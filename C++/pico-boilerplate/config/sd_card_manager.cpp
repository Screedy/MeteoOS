//
// Created by Petr Jurásek on 19.06.2024.
//
#include <stdio.h>

#include "f_util.h"
#include "ff.h"
#include "pico/stdlib.h"
#include "rtc.h"

#include "sd_card_manager.h"
#include "../sensors/SensorManager.h"

sd_card_manager::sd_card_manager()
:pSD(sd_get_by_num(0)), fil(){

    if(mount_sd_card()){
        printf("SD card mounted\n");
        this->mounted = true;
    } else {
        printf("Failed to mount SD card on %s\n", pSD->pcName);
    }

}

sd_card_manager *sd_card_manager::get_instance() {
    static sd_card_manager instance;
    return &instance;
}

FRESULT sd_card_manager::get_fr() {
    return fr;
}

FIL& sd_card_manager::get_fil() {
    return fil;
}

bool sd_card_manager::mount_sd_card() {
    printf("Mounting SD card on %s\n", this->pSD->pcName);
    printf("Pins are: MISO: %d, MOSI: %d, SCK: %d, SS: %d\n", this->pSD->spi->miso_gpio, this->pSD->spi->mosi_gpio, this->pSD->spi->sck_gpio, this->pSD->ss_gpio);


    this->fr = f_mount(&this->pSD->fatfs, this->pSD->pcName, 1);


    if(fr != FR_OK){
        printf("Failed to mount SD card error:%d\n", fr);
        return false;
    }

    this->mounted = true;
    return true;
}

bool sd_card_manager::unmount_sd_card() {
    f_unmount(this->pSD->pcName);

    return true;
}

bool sd_card_manager::is_mounted() {
    return this->mounted;
}

bool sd_card_manager::format() {
    if(!this->mounted){
        printf("SD card is not mounted\n");
        return false;
    }

    printf("Formatting SD card\n");

    FATFS fs; // File system object
    FRESULT fr; // FatFs function common result code
    DWORD work[FF_MAX_SS]; // Work area (larger is better for processing time)

    MKFS_PARM opt = {
            FM_FAT32, 0, 0, 0, 0 // FAT32, 0 for auto
    };

    f_mount(NULL, "", 0); // Unmount the drive

    fr = f_mkfs("0:", &opt, work, sizeof work); // Create FAT volume
    if (fr != FR_OK) {
        printf("Failed to format SD card\n");
        return false;
    }
    printf("SD card formatted\n");

    // Attempt to mount the SD card again
    if (!mount_sd_card()) {
        printf("Failed to mount SD card after formatting\n");
        return false;
    }

    // set SensorManager to default
    SensorManager::getInstance().setDefault();

    return true;
}

bool sd_card_manager::fileExists(const std::string& file_path) {
    FIL file;
    FRESULT res = f_open(&file, file_path.c_str(), FA_READ);
    if (res != FR_OK) {
        return false;
    }

    f_close(&file);
    return true;
}
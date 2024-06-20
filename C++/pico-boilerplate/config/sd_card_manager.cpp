//
// Created by Petr Jurásek on 19.06.2024.
//
#include <stdio.h>

#include "f_util.h"
#include "ff.h"
#include "pico/stdlib.h"
#include "rtc.h"

#include "sd_card_manager.h"

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

    return true;
}

bool sd_card_manager::unmount_sd_card() {
    f_unmount(this->pSD->pcName);

    return true;
}

bool sd_card_manager::is_mounted() {
    return this->mounted;
}

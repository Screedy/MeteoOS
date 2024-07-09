//
// Created by Petr Jurásek on 19.06.2024.
//

#ifndef PICO_BOILERPLATE_SD_CARD_H
#define PICO_BOILERPLATE_SD_CARD_H

#include <string>

#include "f_util.h"
#include "ff.h"

#include "sd_card.h"
#include "hw_config.h"

/*
 * A singleton class that represents the SD card connected to the system.
 */
class sd_card_manager {
public:
    static sd_card_manager *get_instance();
    FRESULT get_fr();
    FIL& get_fil();
    bool fileExists(const std::string& path);
    bool mount_sd_card();
    bool unmount_sd_card();
    bool is_mounted();
    bool format();
private:
    sd_card_t *pSD;
    bool mounted;

    sd_card_manager();
    FRESULT fr;
    FIL fil;
};


#endif //PICO_BOILERPLATE_SD_CARD_H

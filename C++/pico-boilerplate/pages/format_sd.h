//
// Created by Petr Jurásek on 26.06.2024.
//

#ifndef PICO_BOILERPLATE_FORMAT_SD_H
#define PICO_BOILERPLATE_FORMAT_SD_H

#include "../config/Buttons.h"

/*
 * Function that formats the SD card.
 * In the C++ version of the app, this function is going to  put you into the setup wizard.
 * (Since all files are on the SD card)
 *
 * @return true if the SD card was formatted successfully, false if there was an error formatting the SD card.
 */
bool render_format_sd();

#endif //PICO_BOILERPLATE_FORMAT_SD_H

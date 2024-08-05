//
// Created by Petr Jurásek on 02.07.2024.
//

#ifndef PICO_BOILERPLATE_SET_TIME_H
#define PICO_BOILERPLATE_SET_TIME_H

#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/rtc.h"
#include "../config/rtc_module.h"
#include "../config/Buttons.h"

/*
 * Function that renders the set time menu.
 *
 * @return None.
 */
void render_set_time_menu();



#endif //PICO_BOILERPLATE_SET_TIME_H

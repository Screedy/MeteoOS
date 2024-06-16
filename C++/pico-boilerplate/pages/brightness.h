//
// Created by Petr Jurásek on 16.06.2024.
//

#ifndef PICO_BOILERPLATE_BRIGHTNESS_H
#define PICO_BOILERPLATE_BRIGHTNESS_H

#include "../config/config.h"
#include "../config/Display.h"
#include "../graphics/graphics.h"
#include "../graphics/page_elements.h"


/*
 * Function that reads the brightness screen for the display.
 *
 * Has a slider that changes the brightness of the display and saves it to the config file. //TODO: SAVE TO CONFIG FILE
 * @return true if the user wants to save the brightness, false otherwise.
 */
bool render_brightness();

/*
 * Function that renders a graphical slider for the brightness of the display.
 *
 * @param brightness The brightness of the display.
 */
void render_nice_slider(int brightness);

#endif //PICO_BOILERPLATE_BRIGHTNESS_H

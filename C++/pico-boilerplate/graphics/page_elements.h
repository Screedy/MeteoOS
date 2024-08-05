//
// Created by Petr Jurásek on 18.03.2024.
//

#ifndef PICO_BOILERPLATE_PAGE_ELEMENTS_H_H
#define PICO_BOILERPLATE_PAGE_ELEMENTS_H_H

#include "../config/Display.h"
#include "graphics.h"
#include "../config/config.h"
#include "../sensors/SensorManager.h"
#include <cmath>
#include "../pages/Settings.h"

namespace PageElements{
    extern Display& display;
    extern pimoroni::ST7789& driver;
    extern pimoroni::PicoGraphics_PenRGB332& graphics;
}

/*
 * Renders the navigation arrows on the display.
 *
 * @param x The x coordinate of the arrows.
 * @param colour The colour of the arrows. This is an enum from the Colors enum. Default is WHITE.
 * @return None
 */
void render_nav_arrows(int x, int colour = Colors::WHITE);

/*
 * Renders the time of the RP Pico's onboard RTC clock and displays it on the display.
 * The time is displayed in the format "HH:MM".
 *
 * @param time The time to display.
 */
//void parse_time(struct tm* time);

/*
 * Draws the sensor details on the screen.
 *
 * @return None
 */
void render_sensor_details();

/*
 * Renders the home page buttons on the display.
 * This includes the buttons for managing the graph interval. The default interval is Daily. It is being set
 * with an enum from the GraphInterval enum.
 *
 * @param interval The interval of the graph. Default is 0.
 *
 * @return None
 */
void render_homepage_buttons(int interval = 0);

/*
 * Renders the settings page buttons on the display.
 *
 * @return None
 */
void render_settings_buttons();

/*
 * Renders the items list on the display.
 *
 * @param selected_item The index of the selected item. Default is 0.
 * @param page The list of items to display. Default is SettingsItems.list_of_items().
 * @return None
 */
void render_items_list(int selected_item, std::vector<std::string> page);

/*
 * This function is like render_items_list, but it renders the items on a full screen not just the right part.
 *
 * @param selected_item - the index of the selected item
 * @param page - the list of items to render
 *
 * @return void
 */
void render_items_list_full_page(int selected_item, std::vector<std::string> page);

/*
 * Renders a line that separates the different sections of the display.
 */
void render_thick_separator();

#endif //PICO_BOILERPLATE_PAGE_ELEMENTS_H_H

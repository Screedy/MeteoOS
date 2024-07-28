//
// Created by Petr Jurásek on 18.03.2024.
//

#include "page_elements.h"

#include "../config/rtc_module.h"
#include "hardware/rtc.h"

namespace PageElements{
    Display& display = Display::getInstance();
    pimoroni::ST7789& driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332& graphics = display.getGraphics();
    auto& sensor_manager = SensorManager::getInstance();
}

using namespace PageElements;

void render_nav_arrows(int x, int colour){
    graphics.set_pen(colour);

    draw_arrow(x, 7, 16, 180);
    draw_arrow(x, 113, 17, 0);
}

void render_sensor_details(){
    auto& active_sensor = sensor_manager.getSensor(sensor_manager.getActiveSensor());
    std::string current_time = "NOTSET";
    if (is_rtc_set()){
        datetime_t dt = get_current_datetime();
        current_time = get_format_time(dt);
    }

    auto temperature = active_sensor->getTemperature();
    auto humidity = active_sensor->getHumidity();

    graphics.set_pen(Colors::WHITE);
    graphics.text(active_sensor->getName(), pimoroni::Point{34, 7}, 250, 2);
    draw_clock(14, 41);

    graphics.text(current_time, pimoroni::Point{34, 34}, 250, 2);

    draw_thermometer(14, 68);
    graphics.text(std::to_string(std::lround(temperature)) + " °C", pimoroni::Point{34, 61}, 250, 2);

    draw_humidity(14, 96);
    graphics.text(std::to_string(std::lround(humidity)) + " %", pimoroni::Point{34, 88}, 250, 2);
}

void render_homepage_buttons(int interval){
    int active_color = Colors::WHITE;
    int inactive_color = Colors::BLACK;

    Rect box_d(189, 8, 13, 13);
    Rect box_w(204, 8, 13, 13);
    Rect box_m(219, 8, 13, 13);


    (interval == GraphInterval::DAILY) ? graphics.set_pen(active_color) : graphics.set_pen(inactive_color);
    graphics.rectangle(box_d);
    (interval == GraphInterval::WEEKLY) ? graphics.set_pen(active_color) : graphics.set_pen(inactive_color);
    graphics.rectangle(box_w);
    (interval == GraphInterval::MONTHLY) ? graphics.set_pen(active_color) : graphics.set_pen(inactive_color);
    graphics.rectangle(box_m);

    (interval == GraphInterval::DAILY) ? graphics.set_pen(inactive_color) : graphics.set_pen(active_color);
    graphics.text("D", pimoroni::Point{190, 7}, 250, 2);
    (interval == GraphInterval::WEEKLY) ? graphics.set_pen(inactive_color) : graphics.set_pen(active_color);
    graphics.text("W", pimoroni::Point{205, 7}, 250, 2);
    (interval == GraphInterval::MONTHLY) ? graphics.set_pen(inactive_color) : graphics.set_pen(active_color);
    graphics.text("M", pimoroni::Point{220, 7}, 250, 2);

    graphics.set_pen(Colors::WHITE);
    graphics.text("MENU", pimoroni::Point{190, 115}, 250, 2);
}

void render_settings_buttons(){
    graphics.set_pen(Colors::WHITE);
    graphics.text("SETTINGS", pimoroni::Point{135, 7}, 250, 2);
    graphics.text("BACK", pimoroni::Point{190, 115}, 250, 2);
}

void render_items_list(int selected_item, std::vector<std::string> page){
    graphics.set_pen(Colors::WHITE);

    auto number_of_items = page.size();
    auto page_start_item = selected_item - (selected_item % 3);

    for (int i = 0; i < 3; i++){
        if (page_start_item + i >= number_of_items){
            break;
        }

        graphics.set_pen((i == selected_item % 3) ? Colors::WHITE : Colors::BLACK);
        graphics.rectangle(Rect{120, 34 + (i * 27), 110, 15});
        graphics.set_pen((i == selected_item % 3) ? Colors::BLACK : Colors::WHITE);
        graphics.text(page[page_start_item + i], pimoroni::Point{123, 34 + (i * 27)}, 250, 2);

        if (i == selected_item % 3){
            graphics.set_pen(Colors::WHITE);
            graphics.text(">", pimoroni::Point{110, 34 + (i * 27)}, 250, 2);
        } else {
            graphics.set_pen(Colors::BLACK);
            graphics.text(">", pimoroni::Point{110, 34 + (i * 27)}, 250, 2);
        }
    }
}

/*
 * This function is like render_items_list, but it renders the items on a full screen not just the right part.
 *
 * @param selected_item - the index of the selected item
 * @param page - the list of items to render
 *
 * @return void
 */
void render_items_list_full_page(int selected_item, std::vector<std::string> page){
    graphics.set_pen(Colors::WHITE);

    auto number_of_items = page.size();
    auto page_start_item = selected_item - (selected_item % 3);

    for (int i = 0; i < 3; i++){
        if (page_start_item + i >= number_of_items){
            break;
        }

        graphics.set_pen((i == selected_item % 3) ? Colors::WHITE : Colors::BLACK);
        graphics.rectangle(Rect{0, 34 + (i * 27), 240, 15});
        graphics.set_pen((i == selected_item % 3) ? Colors::BLACK : Colors::WHITE);
        graphics.text(page[page_start_item + i], pimoroni::Point{3, 34 + (i * 27)}, 250, 2);

        if (i == selected_item % 3){
            graphics.set_pen(Colors::WHITE);
            graphics.text(">", pimoroni::Point{0, 34 + (i * 27)}, 250, 2);
        } else {
            graphics.set_pen(Colors::BLACK);
            graphics.text(">", pimoroni::Point{0, 34 + (i * 27)}, 250, 2);
        }
    }
}
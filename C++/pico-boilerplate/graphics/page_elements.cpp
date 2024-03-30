//
// Created by Petr Jurásek on 18.03.2024.
//

#include "page_elements.h"

namespace PageElements{
    Display& display = Display::getInstance();
    pimoroni::ST7789& driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332& graphics = display.getGraphics();
}

using namespace PageElements;

void render_nav_arrows(int x, int colour){
    graphics.set_pen(colour);

    draw_arrow(x, 7, 16, 180);
    draw_arrow(x, 113, 17, 0);
}

void render_sensor_details(){
    //TODO: Implement this function
}

void render_homepage_buttons(int interval){
    //TODO: Implement with graph interval

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


//
// Created by Petr Jurásek on 16.06.2024.
//

#include "brightness.h"

namespace Brightness{
    Display& display = Display::getInstance();
    pimoroni::ST7789& driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332& graphics = display.getGraphics();
    Buttons& buttons = Buttons::getInstance();
    SensorManager& sensor_manager = SensorManager::getInstance();
}

using namespace Brightness;

bool render_brightness(){
    //TODO: read brightness from config file
    int brightness = 50;

    while (true){
        if (buttons.is_button_a_pressed()){
            brightness = (brightness + 10) % 100;
        } else if (buttons.is_button_b_pressed()){
            brightness = (brightness - 10) % 100;
        } else if (buttons.is_button_x_pressed()){
            //TODO: save brightness to config file
            return true;
        } else if (buttons.is_button_y_pressed()){
            return false;
        }

        clear_fast();
        graphics.set_pen(Colors::WHITE);
        graphics.text("Brightness", pimoroni::Point{2, 0}, 236, 2);
        render_nav_arrows(0);

        render_nice_slider(brightness);
        driver.update(&graphics);
    }
}

void render_nice_slider(int brightness){
    graphics.set_pen(Colors::GRAY);
    graphics.rectangle(pimoroni::Rect{38, 58, 160, 14});
    graphics.set_pen(Colors::WHITE);
    graphics.text("0.1", pimoroni::Point{10, 58}, 236, 2);
    graphics.text("1.0", pimoroni::Point{200, 58}, 236, 2);

    for (int i = 0; i < 100; i+=10){
        graphics.line(pimoroni::Point{50+i*15, 60}, pimoroni::Point{50+i*15, 70});
    }
}
//
// Created by Petr Jurásek on 26.06.2024.
//

#include "format_sd.h"

#include "../config/config.h"
#include "../config/Display.h"
#include "../config/sd_card_manager.h"
#include "../graphics/page_elements.h"
#include "../config/setup.h"

bool render_format_sd(){
    Display& display = Display::getInstance();
    pimoroni::ST7789& driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332& graphics = display.getGraphics();

    sd_card_manager* sd_card_manager = sd_card_manager::get_instance();
    Buttons& buttons = Buttons::getInstance();

    graphics.set_pen(Colors::BLACK);
    graphics.clear();
    graphics.set_pen(Colors::WHITE);

    graphics.text("Format SD card", pimoroni::Point{2, 0}, 236, 2);
    graphics.set_pen(Colors::RED);
    graphics.text("WARNING: This will delete all data on the SD card!", pimoroni::Point{2, 20}, 236, 2);
    graphics.text("Press Y to confirm", Point{2, DISPLAY_HEIGHT - 40}, 236, 2);
    graphics.set_pen(Colors::GREEN);
    graphics.text("Press X to cancel", Point{2, DISPLAY_HEIGHT - 20}, 236, 2);
    driver.update(&graphics);

    while(!buttons.is_button_y_pressed()){
        if (buttons.is_button_x_pressed()){
            return false;
        }
    }

    sd_card_manager->format();
    initial();
    return true;
}
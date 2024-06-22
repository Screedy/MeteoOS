//
// Created by Petr Jurásek on 21.06.2024.
//

#include "startup.h"

#include "sd_card_manager.h"
#include "Display.h"
#include "../sensors/SensorManager.h"

void startup() {
    // Initialize the Display and it's singleton.
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();

    // Initialize the SD card. If it fails, the system should not continue.
    // Print an error message on the display and exit.
    if(!sd_card_manager::get_instance()->is_mounted()){
        printf("Failed to mount SD card. Exiting...\n");
        graphics.set_pen(Colors::RED);
        graphics.text("Failed to mount SD card", Point{2, 2}, true);
        driver.update(&graphics);
    }

    //TODO: Check if correct.
    initial();

    // Initialize the sensor manager.
    SensorManager::getInstance();
}
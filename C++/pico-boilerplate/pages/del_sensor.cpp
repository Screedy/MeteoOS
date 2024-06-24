//
// Created by Petr Jurásek on 24.06.2024.
//

#include "del_sensor.h"

bool render_del_sensor(){
    // TODO: Test this file
    Display &display = Display::getInstance();
    pimoroni::ST7789 &driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332 &graphics = display.getGraphics();

    SensorManager &sensor_manager = SensorManager::getInstance();

    display.set_color(Colors::BLACK);
    display.clear();
    display.set_color(Colors::WHITE);

    selected_sensor = select_sensor();
    if (selected_sensor == -1) {
        return false;
    }

    sensor_manager.removeSensor(selected_sensor);
    return true;
}

int select_sensor(){
    Display &display = Display::getInstance();
    pimoroni::ST7789 &driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332 &graphics = display.getGraphics();

    SensorManager &sensor_manager = SensorManager::getInstance();

    int sensor_list_length = sensor_manager.getSensorCount();
    int selected_sensor_index = 0;

    while (true){
        if (buttons.is_button_a_pressed()){
            selected_sensor_index = (selected_sensor_index + 1) % sensor_list_length;
        } else if (buttons.is_button_b_pressed()){
            return -1;
        } else if (buttons.is_button_x_pressed()){
            return selected_sensor_index;
        } else if (buttons.is_button_y_pressed()){
            return -1;
        }

        display.set_color(Colors::BLACK);
        display.clear();
        display.set_color(Colors::WHITE);

        int selected_sensor = sensor_manager.getSensor(selected_sensor_index);
        graphiccs.text("Select the sensor you want to delete:", pimoroni::Point{2, 0}, 236, 2);
        graphics.text("GPIO " + std::to_string(sensor_manager.getSensor(selected_sensor_index)->getPin() + " - " + sensor_manager.getSensor(selected_sensor_index)->getName()), pimoroni::Point{2, 40}, 236, 2);

        driver.update(&graphics);

        sleep_ms(200);
    }
}
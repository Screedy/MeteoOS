//
// Created by Petr Jurásek on 24.06.2024.
//

#include "del_sensor.h"
#include "../graphics/page_elements.h"

bool render_del_sensor(){
    // TODO: Test this file
    Display &display = Display::getInstance();
    pimoroni::ST7789 &driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332 &graphics = display.getGraphics();

    SensorManager &sensor_manager = SensorManager::getInstance();

    graphics.set_pen(Colors::BLACK);
    graphics.clear();
    graphics.set_pen(Colors::WHITE);

    #ifdef TEST_BUILD
    printf("... entering select_sensor\n");
    #endif

    int selected_sensor = select_sensor();
    if (selected_sensor == -1) {
        return false;
    }

    sensor_manager.removeSensor(selected_sensor);
    return true;
}

std::vector<std::string> build_sensor_list(){
    SensorManager &sensor_manager = SensorManager::getInstance();
    std::vector<std::unique_ptr<Sensor>> &sensor_list = sensor_manager.getSensors();
    std::vector<std::string> sensor_names;

    for (int i = 0; i < sensor_list.size(); i++){
        sensor_names.push_back("GPIO " + std::to_string(sensor_list[i]->getPin()) + " - " + sensor_list[i]->getName());
    }

    return sensor_names;
}

int select_sensor(){
    Display &display = Display::getInstance();
    pimoroni::ST7789 &driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332 &graphics = display.getGraphics();

    SensorManager &sensor_manager = SensorManager::getInstance();
    Buttons &buttons = Buttons::getInstance();

    int sensor_list_length = sensor_manager.getSensorCount();
    int selected_sensor_index = 0;
    std::vector<std::string> sensor_list = build_sensor_list();

    #ifdef TEST_BUILD
    printf("... sensor_list_length: %d\n", sensor_list_length);
    #endif

    while (true){
        sleep_ms(200);
        if (buttons.is_button_a_pressed()){
            #ifdef TEST_BUILD
            printf("A pressed changing the value from %d to %d\n",
                   selected_sensor_index, (selected_sensor_index + 1) % sensor_list_length);
            #endif

            selected_sensor_index = (selected_sensor_index + 1) % sensor_list_length;
        } else if (buttons.is_button_b_pressed()){
            #ifdef TEST_BUILD
            printf("B pressed changing the value from %d to %d\n",
                   selected_sensor_index, (selected_sensor_index == 0) ? sensor_list_length - 1 : selected_sensor_index - 1);
            #endif

            if (selected_sensor_index == 0){
                selected_sensor_index = sensor_list_length - 1;
            } else {
                selected_sensor_index--;
            }
        } else if (buttons.is_button_x_pressed()){
            return selected_sensor_index;
        } else if (buttons.is_button_y_pressed()){
            return -1;
        }

        graphics.set_pen(Colors::BLACK);
        graphics.clear();
        graphics.set_pen(Colors::WHITE);

        graphics.text("Select sensor to delete:", pimoroni::Point{2, 0}, 236, 2);
        render_items_list_full_page(selected_sensor_index, sensor_list);

        graphics.set_pen(Colors::GREEN);
        graphics.text("OK", Point{DISPLAY_WIDTH - 30, 20}, 200, 2);
        graphics.set_pen(Colors::RED);
        graphics.text("CANCEL", Point{DISPLAY_WIDTH - 65, DISPLAY_HEIGHT - 20}, 200, 2);
        graphics.set_pen(Colors::WHITE);

        driver.update(&graphics);
    }
}
//
// Created by Petr Jurásek on 08.04.2024.
//

#include "add_sensor.h"
#include "../sensors/SensorType.h"

namespace AddSensor{
    Display& display = Display::getInstance();
    pimoroni::ST7789& driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332& graphics = display.getGraphics();
    Buttons& buttons = Buttons::getInstance();
    SensorManager& sensor_manager = SensorManager::getInstance();
}

using namespace AddSensor;

bool render_add_sensor() {
    clear_fast();

    graphics.set_pen(Colors::WHITE);
    graphics.text("Add new sensor", pimoroni::Point{2, 0}, 236, 2);

    SensorType selected_sensor = select_sensor_type();
    if (selected_sensor == SensorType::UNKNOWN) {
        return false;
    }

    int selected_pin = select_sensor_pin();
    if (selected_pin == -1) {
        return false;
    }

    std::string sensor_name = select_sensor_name();
    if (sensor_name.empty()) {
        return false;
    }

    int selected_interval = select_interval();
    if (selected_interval == -1) {
        return false;
    }

    if (selected_sensor == SensorType::DHT11) {
        sensor_manager.addSensor(std::make_unique<DHT11>(DHT11(selected_pin,
                                                               sensor_name, selected_interval)));
    }

    return true;
}

SensorType select_sensor_type() {
    //TODO: sensor_list
    int sensor_list_length = 1;//TODO: sensor_list_length
    int selected_sensor_index = 0;

    sleep_ms(200);

    while (true){
        if (buttons.is_button_a_pressed()){
            selected_sensor_index = (selected_sensor_index + 1) % sensor_list_length;
        } else if (buttons.is_button_b_pressed()){
            selected_sensor_index = (selected_sensor_index - 1) % sensor_list_length;
        } else if (buttons.is_button_x_pressed()){
            return static_cast<SensorType>(selected_sensor_index);
        } else if (buttons.is_button_y_pressed()){
            return SensorType::UNKNOWN;
        }

        clear_fast();
        graphics.set_pen(Colors::WHITE);
        std::string text = "Select the sensor type: " +
                sensor_type_to_string(static_cast<SensorType>(selected_sensor_index));
        graphics.text(text.c_str(), Point{2, 20}, 200, 2);
        driver.update(&graphics);
        sleep_ms(150);
    }
}

int select_sensor_pin() {
    std::vector<int> pin_list = sensor_manager.getAvailablePins();
    int pin_list_length = pin_list.size();
    int selected_pin_index = 0;

    sleep_ms(200);

    while (true){
        if (buttons.is_button_a_pressed()) {
            selected_pin_index = (selected_pin_index + 1) % pin_list_length;
        } else if (buttons.is_button_b_pressed()) {
            if (selected_pin_index == 0) { //C++ modulo operator doesn't work with neg numbers has to be done this way
                selected_pin_index = pin_list_length;
            }
            selected_pin_index = selected_pin_index - 1;
        } else if (buttons.is_button_x_pressed()) {
            return selected_pin_index;
        } else if (buttons.is_button_y_pressed()) {
            return -1;
        }

        clear_fast();
        graphics.set_pen(Colors::WHITE);
        std::string text = "Select the pin: " + std::to_string(pin_list[selected_pin_index]);
        graphics.text(text.c_str(), Point{2, 20}, 200, 2);
        driver.update(&graphics);
        sleep_ms(150);
    }
}

std::string select_sensor_name() {
    std::string name = "";

    auto current_ascii = 65;

    sleep_ms(200);

    while (true){
        if (buttons.is_button_a_pressed()) {
            current_ascii = (current_ascii + 1) % 91;
            if (current_ascii == 0) {
                current_ascii = 65;
            }
        } else if (buttons.is_button_b_pressed()) {
            current_ascii = (current_ascii - 1) % 91;
            if (current_ascii == 64) {
                current_ascii = 90;
            }
        } else if (buttons.is_button_x_pressed()) {
            if (name.length() < 6) {
                name += current_ascii;
                current_ascii = 65;
            }else {
                return name;
            }
        } else if (buttons.is_button_y_pressed()) {
            if (name.length() > 0) {
                name.pop_back();
            } else {
                return "";
            }
        }

        clear_fast();
        graphics.set_pen(Colors::WHITE);
        graphics.text("Name of the sensor:", Point{2, 20}, 200, 2);
        graphics.text(name.c_str(), Point{2, 40}, 200, 2);
        auto length = graphics.measure_text(name.c_str()) + 2;
        graphics.text(std::string(1, current_ascii), Point{length, 40}, 200, 2);

        driver.update(&graphics);
        sleep_ms(150);
    }
}

int select_interval() {
    int interval_time = 0;

    graphics.set_pen(Colors::WHITE);

    while (true){
        if (buttons.is_button_a_pressed()) {
            interval_time = (interval_time + 1) % 61;
        } else if (buttons.is_button_b_pressed()) {
            interval_time = (interval_time - 1) % 61;
        } else if (buttons.is_button_x_pressed()) {
            return interval_time;
        } else if (buttons.is_button_y_pressed()) {
            return -1;
        }

        clear_fast();
        graphics.set_pen(Colors::WHITE);
        std::string text = "Select the interval: " + std::to_string(interval_time);
        graphics.text(text.c_str(), Point{2, 20}, 200, 2);
        driver.update(&graphics);
        sleep_ms(150);
    }
}
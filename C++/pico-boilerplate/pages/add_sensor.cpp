//
// Created by Petr Jurásek on 08.04.2024.
//

#include "add_sensor.h"
#include "../sensors/SensorType.h"
#include "../config/setup.h"

namespace AddSensor{
    Display& display = Display::getInstance();
    pimoroni::ST7789& driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332& graphics = display.getGraphics();
    Buttons& buttons = Buttons::getInstance();
    SensorManager& sensor_manager = SensorManager::getInstance();
}

using namespace AddSensor;

bool render_add_sensor(bool is_setup) {
    clear_fast();

    graphics.set_pen(Colors::WHITE);
    graphics.text("Add new sensor", pimoroni::Point{2, 0}, 236, 2);

#ifdef TEST_BUILD
    printf("Adding a new sensor\nEntering the select_sensor_type function\n");
#endif

    SensorType selected_sensor = select_sensor_type(is_setup);
    if (selected_sensor == SensorType::UNKNOWN) {
        return false;
    }

#ifdef TEST_BUILD
    printf("... Selected sensor type: %s\n", sensor_type_to_string(selected_sensor).c_str());
    printf("Entering the select_sensor_pin function\n");
#endif

    int selected_pin = select_sensor_pin(is_setup);
    if (selected_pin == -1) {
        return false;
    }

#ifdef TEST_BUILD
    printf("... Selected pin: %d\n", selected_pin);
    printf("Entering the select_sensor_name function\n");
#endif

    std::string sensor_name = select_sensor_name(is_setup);
    if (sensor_name.empty()) {
        return false;
    }

#ifdef TEST_BUILD
    printf("... Selected name: %s\n", sensor_name.c_str());
    printf("Entering the select_interval function\n");
#endif

    int selected_interval = select_interval(is_setup);
    if (selected_interval == -1) {
        return false;
    }

#ifdef TEST_BUILD
    printf("... Selected interval: %d\n", selected_interval);

    printf("All the data: \n");
    printf("Sensor type: %s\n Pin: %d\n Name: %s\n Interval: %d\n",
           sensor_type_to_string(selected_sensor).c_str(), selected_pin, sensor_name.c_str(), selected_interval);
    printf("Adding the sensor to the sensor manager\n");
#endif

    if (selected_sensor == SensorType::DHT11) {
        sensor_manager.addSensor(std::make_unique<DHT11>(DHT11(selected_pin,
                                                               sensor_name, selected_interval)));
    }

    return true;
}

SensorType select_sensor_type(bool is_setup) {
    std::vector<std::string> possibleSensors = sensorTypes;
    int sensor_list_length = possibleSensors.size();
    int selected_sensor_index = 0;

    sleep_ms(500);

    while (true){
        if (buttons.is_button_a_pressed()){
            selected_sensor_index = (selected_sensor_index + 1) % sensor_list_length;
        } else if (buttons.is_button_b_pressed()){
            if (selected_sensor_index == 0) { //C++ modulo operator doesn't work with neg numbers has to be done this way
                selected_sensor_index = sensor_list_length;
            }
            selected_sensor_index = selected_sensor_index - 1;
        } else if (buttons.is_button_x_pressed()){
#ifdef TEST_BUILD
            printf("Selected sensor: %s\n", possibleSensors[selected_sensor_index].c_str());
#endif

            if (is_setup) {
                help_interrupt();
            } else {
                return static_cast<SensorType>(selected_sensor_index);
            }
        } else if (buttons.is_button_y_pressed()){
#ifdef TEST_BUILD
            printf("User canceled the operation\n");
#endif

            if (is_setup) {
                return static_cast<SensorType>(selected_sensor_index);
            }

            return SensorType::UNKNOWN;
        }

        clear_fast();
        graphics.set_pen(Colors::WHITE);

        graphics.text("ADD SENSOR", Point{30, 8}, 200, 2);
        render_nav_arrows(2, Colors::WHITE);

        std::string text = "Select the sensor type: " +
                           sensor_type_to_string(static_cast<SensorType>(selected_sensor_index));
        graphics.text(text.c_str(), Point{2, 50}, 200, 2);

        graphics.set_pen(Colors::GREEN);
        // If the function is called from the setup, act as OK button, otherwise cancel button.
        if (is_setup) {
            graphics.text("OK", Point{DISPLAY_WIDTH - 30, DISPLAY_HEIGHT - 20}, 200, 2);
            graphics.set_pen(Colors::RED);
            graphics.text("HELP", Point{DISPLAY_WIDTH - 45, 20}, 200, 2);
        } else {
            graphics.text("OK", Point{DISPLAY_WIDTH - 30, 20}, 200, 2);
            graphics.set_pen(Colors::RED);
            graphics.text("CANCEL", Point{DISPLAY_WIDTH - 65, DISPLAY_HEIGHT - 20}, 200, 2);
        }
        graphics.set_pen(Colors::WHITE);

        driver.update(&graphics);
        sleep_ms(200);
    }
}

int select_sensor_pin(bool is_setup) {
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
            #ifdef TEST_BUILD
                printf("Selected pin: %d\n", pin_list[selected_pin_index]);
            #endif

            if (is_setup) {
                help_interrupt();
            } else {
                return pin_list[selected_pin_index];
            }
        } else if (buttons.is_button_y_pressed()) {
            #ifdef TEST_BUILD
                printf("User canceled the operation on selecting a pin.\n");
            #endif

            // If the function is called from the setup, act as OK button, otherwise cancel button.
            if (is_setup) {
                return pin_list[selected_pin_index];
            }

            return -1;
        }

        clear_fast();
        graphics.set_pen(Colors::WHITE);

        graphics.text("ADD SENSOR", Point{30, 8}, 200, 2);
        render_nav_arrows(2, Colors::WHITE);

        std::string text = "Select sensor pin: " + std::to_string(pin_list[selected_pin_index]);
        graphics.text(text.c_str(), Point{2, 60}, 200, 2);

        graphics.set_pen(Colors::GREEN);

        // If the function is called from the setup, act as OK button, otherwise cancel button.
        if (is_setup) {
            graphics.text("OK", Point{DISPLAY_WIDTH - 65, DISPLAY_HEIGHT - 20}, 200, 2);
            graphics.set_pen(Colors::RED);
            graphics.text("HELP", Point{DISPLAY_WIDTH - 30, 20}, 200, 2);
        } else {
            graphics.text("OK", Point{DISPLAY_WIDTH - 30, 20}, 200, 2);
            graphics.set_pen(Colors::RED);
            graphics.text("CANCEL", Point{DISPLAY_WIDTH - 65, DISPLAY_HEIGHT - 20}, 200, 2);
        }
        graphics.set_pen(Colors::WHITE);

        driver.update(&graphics);
        sleep_ms(150);
    }
}

std::string select_sensor_name(bool is_setup) {
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_";
    const int characters_length = sizeof(characters) - 1;
    int current_index = 0;
    std::string name = "";




    while (true){
        sleep_ms(200);
        if (buttons.is_button_a_pressed()){
            current_index = (current_index + 1) % characters_length;
        } else if (buttons.is_button_b_pressed()){
            if (current_index == 0) {
                current_index = characters_length;
            }
            current_index = current_index - 1;
        } else if (buttons.is_button_x_pressed()){
            if (name.length() < 6) {
                name += (characters[current_index] == '_') ? ' ' : characters[current_index];
                current_index = 0;
            } else {
                return name;
            }
        } else if (buttons.is_button_y_pressed()){
            if (name.length() > 0) {
                name.pop_back();
            } else {
                if (is_setup) {
                    help_interrupt();
                } else {
                    return "";
                }
            }
        }

        clear_fast();
        graphics.set_pen(Colors::WHITE);

        graphics.text("ADD SENSOR", Point{30, 8}, 200, 2);
        render_nav_arrows(2, Colors::WHITE);

        graphics.text("Name of the sensor:", Point{2, 50}, 200, 2);
        graphics.text(name.c_str(), Point{2, 70}, 200, 2);

        auto length = graphics.measure_text(name.c_str()) + 2;
        if (name.length() < 6){
            graphics.set_pen(Colors::GRAY);
            graphics.text(std::string(1, characters[current_index]), Point{length, 70}, 200, 2);
        }

        graphics.set_pen(Colors::GREEN);
        if (name.length() == 6) {
            graphics.text("OK", Point{DISPLAY_WIDTH - 30, 20}, 200, 2);
        } else {
            graphics.text("ADD", Point{DISPLAY_WIDTH - 35, 20}, 200, 2);
        }

        graphics.set_pen(Colors::RED);
        if (name.length() == 0) {
            if (is_setup) {
                graphics.text("HELP", Point{DISPLAY_WIDTH - 45, DISPLAY_HEIGHT - 20}, 200, 2);
            } else {
                graphics.text("CANCEL", Point{DISPLAY_WIDTH - 65, DISPLAY_HEIGHT - 20}, 200, 2);
            }
        } else {
            graphics.text("DEL", Point{DISPLAY_WIDTH - 35, DISPLAY_HEIGHT - 20}, 200, 2);
        }

        driver.update(&graphics);
    }
}

int select_interval(bool is_setup) {
    int interval_time = 0;

    graphics.set_pen(Colors::WHITE);

    while (true){
        sleep_ms(200);
        if (buttons.is_button_a_pressed()) {
            interval_time = (interval_time + 1) % 61;
        } else if (buttons.is_button_b_pressed()) {
            interval_time = (interval_time - 1) % 61;
        } else if (buttons.is_button_x_pressed()) {
            if (is_setup) {
                help_interrupt();
            } else {
                return interval_time;
            }
        } else if (buttons.is_button_y_pressed()) {
            if (is_setup) {
                return interval_time;
            }

            return -1;
        }

        clear_fast();
        graphics.set_pen(Colors::WHITE);
        std::string text = "Select the interval: " + std::to_string(interval_time) + " min";
        graphics.text(text.c_str(), Point{2, 20}, 200, 2);

        if (is_setup) {

        }

        graphics.set_pen(Colors::GREEN);
        // If the function is called from the setup, act as OK button, otherwise cancel button.
        if (is_setup) {
            graphics.text("OK", Point{DISPLAY_WIDTH - 65, DISPLAY_HEIGHT - 20}, 200, 2);
            graphics.set_pen(Colors::RED);
            graphics.text("HELP", Point{DISPLAY_WIDTH - 30, 20}, 200, 2);
        } else {
            graphics.text("OK", Point{DISPLAY_WIDTH - 30, 20}, 200, 2);
            graphics.set_pen(Colors::RED);
            graphics.text("CANCEL", Point{DISPLAY_WIDTH - 65, DISPLAY_HEIGHT - 20}, 200, 2);
        }
        graphics.set_pen(Colors::WHITE);

        driver.update(&graphics);
    }
}
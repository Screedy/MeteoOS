//
// Created by Petr Jurásek on 06.04.2024.
//

#include "Settings.h"

namespace Settings{
    Display& display = Display::getInstance();
    pimoroni::ST7789& driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332& graphics = display.getGraphics();
    Buttons& buttons = Buttons::getInstance();
}

using namespace Settings;

std::string SettingsItems::SettingsToString(SettingsItem item) {
    switch (item) {
        case AddSensor:
            return "AddSensor";
        case RemSensor:
            return "RemSensor";
        case Brightness:
            return "Brightness";
        case FormatSD:
            return "FormatSD";
        case DelData:
            return "DelData";
        default:
            return "Unknown";
    }
}

std::vector<std::string> SettingsItems::list_of_items() {
    std::vector<std::string> items;
    for (int i = 0; i < SettingsItems::NumberOfItems; i++) {
        items.push_back(SettingsItems::SettingsToString(static_cast<SettingsItems::SettingsItem>(i)));
    }
    return items;
}

std::function<void()> SettingsItems::get_function(int selected_item) {
    switch (selected_item) {
        case AddSensor:
            return SettingsFunctions::add_sensor;
        case RemSensor:
            return SettingsFunctions::remove_sensor;
        case Brightness:
            return SettingsFunctions::change_brightness;
        case FormatSD:
            return SettingsFunctions::format_sd;
        case DelData:
            return SettingsFunctions::del_data;
        default:
            return [](){};
    }
}

void SettingsFunctions::add_sensor() {
    //TODO: Implement adding sensor page
    printf("Adding sensor\n");
}

void SettingsFunctions::remove_sensor() {
    //TODO: Implement removing sensor page§
    printf("Removing sensor\n");
}

void SettingsFunctions::change_brightness() {
    //TODO: Implement changing brightness page
    printf("Changing brightness\n");
}

void SettingsFunctions::format_sd() {
    //TODO: Implement formatting SD card page
    printf("Formatting SD card\n");
}

void SettingsFunctions::del_data() {
    //TODO: Implement deleting data page
    printf("Deleting data\n");
}

void render_settings(int selected_item) {
    clear_fast();
    graphics.set_pen(Colors::WHITE);

    render_sensor_details();
    render_nav_arrows(110);

    graphics.line(Point{100, 16}, Point{100, 120});
    graphics.line(Point{101, 16}, Point{101, 120}); //TODO: Implement these as a function
    graphics.line(Point{102, 16}, Point{102, 120});

    render_settings_buttons();

    //printf("Debug: %d\n", selected_item);

    render_items_list(selected_item, SettingsItems::list_of_items());

    driver.update(&graphics);
}

void settings_loop(){
    int selected_item = 0;
    auto settings_list = SettingsItems::list_of_items();

    while (true){
        sleep_ms(300);
        if (buttons.is_button_x_pressed()){
            SettingsItems::get_function(selected_item)();
        } else if (buttons.is_button_y_pressed()){
            return;
        } else if (buttons.is_button_a_pressed()){
            selected_item = (selected_item - 1) % settings_list.size();
        } else if (buttons.is_button_b_pressed()){
            selected_item = (selected_item + 1) % settings_list.size();
        }

        render_settings(selected_item);
    }
}

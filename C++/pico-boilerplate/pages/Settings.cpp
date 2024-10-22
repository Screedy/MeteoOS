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
        case SetTime:
            return "SetTime";
        case ResetGraph:
            return "ResetGraph";
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
        case SetTime:
            return SettingsFunctions::set_time;
        case ResetGraph:
            return SettingsFunctions::reset_graph;
        default:
            return [](){};
    }
}

void SettingsFunctions::add_sensor() {
    #ifdef TEST_BUILD
    printf("Adding sensor\n");
    #endif
    render_add_sensor();
}

void SettingsFunctions::remove_sensor() {
    #ifdef TEST_BUILD
    printf("Removing sensor\n");
    #endif
    render_del_sensor();
}

void SettingsFunctions::change_brightness() {
    #ifdef TEST_BUILD
    printf("Changing brightness\n");
    #endif
    render_brightness();
}

void SettingsFunctions::format_sd() {
    #ifdef TEST_BUILD
    printf("Formatting SD card\n");
    #endif
    render_format_sd();
}

void SettingsFunctions::del_data() {
    #ifdef TEST_BUILD
    printf("Deleting data\n");
    #endif
    render_del_data();
}

void SettingsFunctions::set_time() {
    #ifdef TEST_BUILD
    printf("Setting time\n");
    #endif
    render_set_time_menu();
}

void SettingsFunctions::reset_graph() {
    #ifdef TEST_BUILD
    printf("Resetting graph\n");
    #endif
    render_reset_graph();
}

void render_settings(int selected_item) {
    clear_fast();
    graphics.set_pen(Colors::WHITE);

    auto& sensor_manager = SensorManager::getInstance();
    auto sensor = sensor_manager.getSensor(sensor_manager.getActiveSensor());
    sensor->read();

    render_sensor_details();
    render_nav_arrows(110);

    graphics.line(Point{100, 16}, Point{100, 120});
    graphics.line(Point{101, 16}, Point{101, 120}); //NOTE: Implement these as a function (minor, optional)
    graphics.line(Point{102, 16}, Point{102, 120});

    render_settings_buttons();

    render_items_list(selected_item, SettingsItems::list_of_items());

    driver.update(&graphics);
}

void settings_loop(){
    int selected_item = 0;
    auto settings_list = SettingsItems::list_of_items();

    while (true){
        if (buttons.is_button_x_pressed()){
            SettingsItems::get_function(selected_item)();
        } else if (buttons.is_button_y_pressed()){
            return;
        } else if (buttons.is_button_a_held()){
            if (selected_item == 0){
                selected_item = settings_list.size() - 1;
            } else {
                selected_item = (selected_item - 1) % settings_list.size();
            }
        } else if (buttons.is_button_b_held()){
            selected_item = (selected_item + 1) % settings_list.size();
        }

        render_settings(selected_item);
    }
}


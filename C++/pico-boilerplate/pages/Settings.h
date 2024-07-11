//
// Created by Petr Jurásek on 06.04.2024.
//

#ifndef PICO_BOILERPLATE_SETTINGS_H
#define PICO_BOILERPLATE_SETTINGS_H

#include <vector>
#include <string>
#include <functional>

#include "../graphics/graphics.h"
#include "../graphics/page_elements.h"
#include "../config/config.h"

//Include all the pages that are used in the settings page
#include "add_sensor.h"
#include "brightness.h"
#include "del_sensor.h"
#include "format_sd.h"
#include "del_data.h"
#include "set_time.h"
#include "reset_graph.h"


namespace Settings{
    extern Display& display;
    extern pimoroni::ST7789& driver;
    extern pimoroni::PicoGraphics_PenRGB332& graphics;
    extern Buttons& buttons;
}

/*
 * A class that represents the settings items.
 * This class is used to get the settings items as strings and to get the functions that are associated with the items.
 */
class SettingsItems {
private:
    /*
     * An enum that represents the settings items.
     */
    enum SettingsItem {
        AddSensor,
        RemSensor,
        Brightness,
        FormatSD,
        DelData,
        SetTime,
        ResetGraph,
        NumberOfItems
    };
    /*
     * Converts the settings item to a string.
     *
     * @param item The settings item to convert.
     * @return The settings item as a string.
     */
    static std::string SettingsToString(SettingsItem item);

public:
    SettingsItems();
    /*
     * Returns a list of the settings items as strings.
     *
     * @return A list of the settings items as strings.
     */
    static std::vector<std::string> list_of_items();
    /*
     * Returns the function that is associated with the selected item.
     *
     * @param selected_item The index of the selected item.
     * @return The function that is associated with the selected item.
     */
    static std::function<void()> get_function(int selected_item);

};

/*
 * A class that contains the functions that are associated with the settings items.
 */
class SettingsFunctions {
public:
    static void add_sensor();
    static void remove_sensor();
    static void change_brightness();
    static void format_sd();
    static void del_data();
    static void set_time();
    static void reset_graph();
};

/*
 * Renders the settings page on the display.
 *
 * @param selected_item The index of the selected item. Default is 0.
 * @return None
 */
void render_settings(int selected_item = 0);

/*
 * The loop that is used to navigate through the settings page.
 *
 * @return None
 */
void settings_loop();


#endif //PICO_BOILERPLATE_SETTINGS_H

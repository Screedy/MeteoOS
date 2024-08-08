//
// Created by Petr Jurásek on 06.07.2024.
//

#include <iomanip>
#include <sstream>
#include <iostream>

#include "concrete_strategy_weekly.h"
#include "../../config/Display.h"
#include "strategy_graph_interval.h"
#include "../../config/sd_card_manager.h"
#include "../../config/rtc_module.h"
#include "../../utils/string_modifiers.h"

void ConcreteStrategyWeekly::renderGraph(datetime_t date, Sensor* sensor, bool force_redraw) {
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();

    graphics.set_pen(Colors::WHITE);
    graphics.text("WEEK1 WEEK2 WEEK3 WEEK4", Point(130, 105), 250, 1);
    graphics.line(Point(125, 103), Point(234, 103));
    graphics.line(Point(125, 103), Point (125, 20));

    std::vector<float> temp = {0, 0, 0, 0};
    std::vector<float> hum = {0, 0, 0, 0};

    if (!force_redraw) {
         getWeeklyValuesFromFile(temp, hum, sensor);
    } else {
        generateWeeklyValues(temp, hum, sensor, date);
    }

    renderWeeklyGraph(temp, hum);
}

void ConcreteStrategyWeekly::renderWeeklyGraph(const std::vector<float>& temp, const std::vector<float>& hum) {
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();
    float min_temp, max_temp, min_hum, max_hum;

    uint8_t precision = 0; // Number of decimal places to display

    std::ostringstream min_temp_str, max_temp_str, min_hum_str, max_hum_str, temp_middle_str, hum_middle_str;

    min_temp = getMin(temp);
    min_temp_str << std::fixed << std::setprecision(precision) << min_temp;
    max_temp = getMax(temp);
    max_temp_str << std::fixed << std::setprecision(precision) << max_temp;

    min_hum = getMin(hum);
    min_hum_str << std::fixed << std::setprecision(precision) << min_hum;
    max_hum = getMax(hum);
    max_hum_str << std::fixed << std::setprecision(precision) << max_hum;

    // Calculate the middle value of the temperature and humidity
    float temp_middle = (min_temp + max_temp) / 2;
    temp_middle_str << std::fixed << std::setprecision(precision) << temp_middle;

    float hum_middle = (min_hum + max_hum) / 2;
    hum_middle_str << std::fixed << std::setprecision(precision) << hum_middle;

    // Render these values on the screen on appropriate positions
    graphics.text(max_temp_str.str(), Point(108, 20), 250, 1);
    graphics.text(temp_middle_str.str(), Point(108, 60), 250, 1);
    graphics.text(min_temp_str.str(), Point(108, 98), 250, 1);

    // printf("Temp values: %f %f %f %f\n", temp[0], temp[1], temp[2], temp[3]);

    graphics.set_pen(Colors::WHITE);

    for (int i = 0; i < 3; i++) {
        if (temp[i] != -404.0f && temp[i + 1] != -404.0f) {
            graphics.line(Point(140 + i * 30, temperature_to_pixel(temp[i], max_temp, min_temp)),
                          Point(140 + (i + 1) * 30, temperature_to_pixel(temp[i + 1], max_temp, min_temp)));
        } else if (temp[i] != -404.0f) {
            // printf("Drawing pixel at %d %d\n", 130 + i * 32, temperature_to_pixel(temp[i], max_temp, min_temp));
            graphics.pixel(Point(140 + i * 30, temperature_to_pixel(temp[i], max_temp, min_temp)));
        } else if (temp[i + 1] != -404.0f) {
            graphics.pixel(Point(140 + (i + 1) * 30, temperature_to_pixel(temp[i + 1], max_temp, min_temp)));
        }
    }

    if (temp[3] != -404.0f) {
        graphics.line(Point(140 + 3 * 30, temperature_to_pixel(temp[3], max_temp, min_temp)),
                      Point(140 + 4 * 30, temperature_to_pixel(temp[3], max_temp, min_temp)));
    }
}

void ConcreteStrategyWeekly::getWeeklyValuesFromFile(std::vector<float>& temp, std::vector<float>& hum, Sensor* sensor) {
    sd_card_manager* sd_card_manager = sd_card_manager::get_instance();

    // Look into 0:/sensors/measurements/"sensor_name"_weekly.txt file (Should exist - checked before)
    // Line format: temp1;temp2;temp3;temp4
    std::string clean_name = sensor->getName();
    clean_name.erase(std::remove(clean_name.begin(), clean_name.end(), '\0'), clean_name.end());
    std::string file_path = "0:/sensors/measurements/" + clean_name + "_weekly.txt";

    FIL file;
    FRESULT res = f_open(&file, file_path.c_str(), FA_READ);
    if (res != FR_OK) {
        printf("Failed to open file %s\n", file_path.c_str());
        return;
    }

    char line[100];
    f_gets(line, 100, &file);
    f_close(&file);

    std::vector<std::string> values = split(line, ';');
    for (int i = 0; i < 4; i++) {
        temp[i] = std::stof(values[i]);
    }

    for (int i = 0; i < 4; i++) {
        hum[i] = -404.0f; // NOTE: No humidity values are being stored here right now.
        // NOTE: There was no room on the display. This can be changed in the future.
    }
}

void ConcreteStrategyWeekly::generateWeeklyValues(std::vector<float>& temp,
                                                  std::vector<float>& hum, Sensor* sensor, datetime_t date) {
    // Use the generateOneDayValues function from the StrategyGraphInterval class to get the values for the given days

    // NOTE: This is hardcoded to week that has values pregenerated in a file. So that both MicroPython and C++ version
    // have the same test generated, and thus we can compare the time.
    // date.year = 2024;
    // date.month = 2;
    // date.day = 15;
    // date.dotw = 3;

    datetime_t start = date;
    start.day = 1;


    int num_days_in_month = getNumDaysInMonth(date.month, date.year);

    #ifdef TEST_BUILD
    printf("Start of the week: %d-%d-%d\n", start.year, start.month, start.day);
    sleep_ms(2000);
    #endif

    sd_card_manager* sd_card_manager = sd_card_manager::get_instance();
    std::string clean_name = sensor->getName();
    clean_name.erase(std::remove(clean_name.begin(), clean_name.end(), '\0'), clean_name.end());
    std::string file_path = "0:/measurements/" + clean_name + ".txt";

    FIL file;
    FRESULT res = f_open(&file, file_path.c_str(), FA_READ);
    if (res != FR_OK) {
        printf("Failed to open file %s\n", file_path.c_str());
        return;
    }

    // Generate values for the month (4 weeks)
    for(int i = 0; i < 4; i++){
        temp[i] = 0.0f;
        hum[i] = 0.0f;
        int days_with_values = 0;

        for(int j = 0; j < 7; j++){ // Week has 7 days.
            std::array<float, 2> values = generateOneDayValues(start, file);

            if(values[0] != -404.0f || values[1] != -404.0f){
                temp[i] += values[0];
                hum[i] += values[1];
                days_with_values++;
            }

            start = add_days(start, 1);
        }

        if (days_with_values == 0) {
            temp[i] = -404.0f;
            hum[i] = -404.0f;
        } else {
            temp[i] /= days_with_values;
            hum[i] /= days_with_values;
        }

        days_with_values = 0;
    }

    f_close(&file);

    // Save the values in a file for later use at 0:/sensors/measurements/"sensor_name"_weekly.txt
    std::string values_str = "";
    for (int i = 0; i < 4; i++) {
        values_str += std::to_string(temp[i]);
        if (i != 3) {
            values_str += ";";
        }
    }

    file_path = "0:/sensors/measurements/" + clean_name + "_weekly.txt";
    res = f_open(&file, file_path.c_str(), FA_WRITE | FA_CREATE_ALWAYS);
    if (res != FR_OK) {
        printf("Failed to open file %s\n", file_path.c_str());
        return;
    }

    f_puts(values_str.c_str(), &file);
    f_close(&file);
}

std::string ConcreteStrategyWeekly::getIntervalName() {
    return "_weekly";
}
//
// Created by Petr Jurásek on 06.07.2024.
//

#include <iomanip>
#include <sstream>
#include <iostream>

#include "concrete_strategy_daily.h"
#include "../../config/Display.h"
#include "strategy_graph_interval.h"

void ConcreteStrategyDaily::renderGraph(datetime_t date, Sensor* sensor, bool force_redraw) {
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();

    graphics.set_pen(Colors::WHITE);
    graphics.text("MO TU WE TH FR SA SU", Point(130, 105), 250, 1);
    graphics.line(Point(125, 103), Point(234, 103));
    graphics.line(Point(125, 103), Point (125, 20));

    std::vector<float> temp;
    std::vector<float> hum;

    //Temporary values
    temp = {20.0f, 21.0f, 22.0f, 23.0f, 24.0f, 25.0f, 26.0f};
    hum = {50.0f, 51.0f, 52.0f, 53.0f, 54.0f, 55.0f, 56.0f};

    if (!force_redraw) {
         //TODO: get_measurements(sensor); returns the measurements from a file
         //temp = sensor->get_measurements(date, "temp");
         //hum = sensor->get_measurements(date, "hum"); ... nějak takto
    } else {
        //TODO: Return the average temperature and humidity for the given date from file in that week period

        //TODO: Save them in a file for later use if not force_redraw
    }

    renderDailyGraph(temp, hum);
}

void ConcreteStrategyDaily::renderDailyGraph(const std::vector<float>& temp, const std::vector<float>& hum) {
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
    float temp_middle_value = (min_temp + max_temp) / 2;
    temp_middle_str << std::fixed << std::setprecision(precision) << temp_middle_value;

    float hum_middle_value = (min_hum + max_hum) / 2;
    hum_middle_str << std::fixed << std::setprecision(precision) << hum_middle_value;

    // Render these values on the screen on appropriate positions
    graphics.text(max_temp_str.str(), Point(108, 20), 250, 1);
    graphics.text(temp_middle_str.str(), Point(108, 60), 250, 1);
    graphics.text(min_temp_str.str(), Point(108, 98), 250, 1);

    graphics.set_pen(Colors::BLUE);
    for (int i = 0; i < 7; i++) {
        if (temp[i] != -404.0f && temp[i + 1] != -404.0f) {
            graphics.line(Point(130 + i * 16, temperature_to_pixel(temp[i], max_temp, min_temp)),
                          Point(130 + (i + 1) * 16, temperature_to_pixel(temp[i + 1], max_temp, min_temp)));
        } else if (temp[i] != -404.0f) {
            graphics.pixel(Point(130 + i * 16, temperature_to_pixel(temp[i], max_temp, min_temp)));
        } else if (temp[i + 1] != -404.0f) {
            graphics.pixel(Point(130 + (i + 1) * 16, temperature_to_pixel(temp[i + 1], max_temp, min_temp)));
        }
    }

}
//
// Created by Petr Jurásek on 06.07.2024.
//

#ifndef PICO_BOILERPLATE_STRATEGY_GRAPH_INTERVAL_H
#define PICO_BOILERPLATE_STRATEGY_GRAPH_INTERVAL_H

#include <string>
#include <array>
#include <vector>
#include "../../config/Display.h"
#include "../../config/config.h"
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"
#include "../../sensors/Sensor.h"
#include "../../config/sd_card_manager.h"

/*
 * The strategy pattern is a behavioral design pattern that enables selecting an algorithm at runtime.
 * The StrategyGraphInterval selects the algorithm to render the graph for a given time interval.
 */
class StrategyGraphInterval {
public:
    /*
     * Renders the graph for the given date and sensor.
     * This method should be implemented by the child classes.
     *
     * @param date: Date for which the graph should be rendered.
     * @param sensor: Sensor for which the graph should be rendered.
     * @param force_redraw: If true, the graph will be redrawn even if it was already rendered for the given date.
     */
    virtual void renderGraph(datetime_t date, Sensor* sensor, bool force_redraw) = 0;

    /*
     * Returns the name of the interval.
     * This method should be implemented by the child classes.
     *
     * @return std::string: Name of the interval.
     */
    virtual std::string getIntervalName() = 0;

    /*
     * Returns the minimum value from the given vector of floats.
     *
     * @param values: Vector of floats from which the minimum value should be returned.
     */
    float getMin(const std::vector<float>& values);

    /*
     * Returns the maximum value from the given vector of floats.
     *
     * @param values: Vector of floats from which the maximum value should be returned.
     */
    float getMax(const std::vector<float>& values);

    /*
     * Converts the given temperature value to a range of pixels.
     * It uses a range from 20 to 100 pixels on the screen. If the temperature is almost the same as the minimum
     * temperature, it will be around the 20th pixel mark.
     *
     * @param float temp: Temperature value that should be converted to pixels.
     * @param float min_temp: Minimum temperature value from the given vector of temperatures.
     * @param float max_temp: Maximum temperature value from the given vector of temperatures.
     *
     * @return int: Pixel value for the given temperature.
     */
    int temperature_to_pixel(float temp, float min_temp, float max_temp);
    std::array<float, 2> generateOneDayValues(datetime_t day, FIL& file);

    };

#endif //PICO_BOILERPLATE_STRATEGY_GRAPH_INTERVAL_H

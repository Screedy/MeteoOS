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
    virtual void renderGraph(datetime_t date, Sensor* sensor, bool force_redraw) = 0;
    float getMin(const std::vector<float>& values);
    float getMax(const std::vector<float>& values);
    int temperature_to_pixel(float temp, float min_temp, float max_temp);
    std::array<float, 2> generateOneDayValues(datetime_t day, FIL& file);

    };

#endif //PICO_BOILERPLATE_STRATEGY_GRAPH_INTERVAL_H

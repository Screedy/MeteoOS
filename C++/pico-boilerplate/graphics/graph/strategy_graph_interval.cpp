//
// Created by Petr Jurásek on 09.07.2024.
//

#include "strategy_graph_interval.h"

float StrategyGraphInterval::getMin(const std::vector<float>& values) {
    float min = std::numeric_limits<float>::max();
    for (float value : values) {
        if (value != -404.0f && value < min) {
            min = value;
        }
    }
    return min;
}

float StrategyGraphInterval::getMax(const std::vector<float>& values) {
    float max = std::numeric_limits<float>::min();
    for (float value : values) {
        if (value != -404.0f && value > max) {
            max = value;
        }
    }
    return max;
}

int StrategyGraphInterval::temperature_to_pixel(float temp, float min_temp, float max_temp) {
    int pixel_min = 20;
    int pixel_max = 100;

    #ifdef TEST_BUILD
        printf("The pixel y value is: %d\n", (int) (pixel_max + ((temp - min_temp) * (pixel_min - pixel_max)) / (max_temp - min_temp)));
    #endif

    return (int) (pixel_max + ((temp - min_temp) * (pixel_min - pixel_max)) / (max_temp - min_temp));
}
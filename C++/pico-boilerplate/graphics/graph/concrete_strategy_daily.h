//
// Created by Petr Jurásek on 06.07.2024.
//

#ifndef PICO_BOILERPLATE_CONCRETE_STRATEGY_DAILY_H
#define PICO_BOILERPLATE_CONCRETE_STRATEGY_DAILY_H

#include <vector>
#include "strategy_graph_interval.h"

/*
 * Concrete strategy for rendering daily graph. It is a subclass of StrategyGraphInterval.
 * It overrides renderGraph method and provides its own implementation.
 *
 * @see StrategyGraphInterval
 */
class ConcreteStrategyDaily : public StrategyGraphInterval {
public:
    /*
     * Renders daily graph for given date and sensor.
     *
     * @param date: Date for which the graph should be rendered.
     * @param sensor: Sensor for which the graph should be rendered.
     * @param force_redraw: If true, the graph will be redrawn even if it was already rendered for the given date.
     */
    void renderGraph(datetime_t date, Sensor* sensor, bool force_redraw) override;
private:
    /*
     * Renders daily graph for given temperature and humidity values.
     *
     * @param temp: Vector of temperature values. It should contain 7 values, one for each day of the week.
     *              If the value is -404 it means that measurement for that day is missing.
     * @param hum: Vector of humidity values. It should contain 7 values, one for each day of the week.
     *              If the value is -404 it means that measurement for that day is missing.
     */
    void renderDailyGraph(const std::vector<float>& temp, const std::vector<float>& hum);

    /*
     * Gets daily temperature and humidity values from the file.
     *
     * @param temp: Vector where the temperature values will be stored.
     * @param hum: Vector where the humidity values will be stored.
     * @param sensor: Sensor for which the values should be retrieved.
     */
    void getDailyValuesFromFile(std::vector<float>& temp, std::vector<float>& hum, Sensor* sensor);

    /*
     * Generates daily temperature and humidity values for the given date.
     *
     * @param temp: Vector where the temperature values will be stored.
     * @param hum: Vector where the humidity values will be stored.
     * @param sensor: Sensor for which the values should be generated.
     * @param date: Date for which the values should be generated.
     */
    void generateDailyValues(std::vector<float>& temp, std::vector<float>& hum, Sensor* sensor, datetime_t date);
};

#endif //PICO_BOILERPLATE_CONCRETE_STRATEGY_DAILY_H

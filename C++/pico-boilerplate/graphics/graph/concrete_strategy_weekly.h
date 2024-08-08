//
// Created by Petr Jurásek on 06.07.2024.
//

#ifndef PICO_BOILERPLATE_CONCRETE_STRATEGY_WEEKLY_H
#define PICO_BOILERPLATE_CONCRETE_STRATEGY_WEEKLY_H

#include "strategy_graph_interval.h"
#include "../../pages/set_time.h"

/*
 * Concrete strategy for rendering weekly graph. It is a subclass of StrategyGraphInterval.
 * It overrides renderGraph method and provides its own implementation.
 *
 * @see StrategyGraphInterval
 */
class ConcreteStrategyWeekly : public StrategyGraphInterval {
public:
    /*
     * Renders weekly graph for given date and sensor.
     *
     * @param date: Date for which the graph should be rendered.
     * @param sensor: Sensor for which the graph should be rendered.
     * @param force_redraw: If true, the graph will be redrawn even if it was already rendered for the given date.
     */
    void renderGraph(datetime_t date, Sensor* sensor, bool force_redraw) override;

    /*
     * Returns the name of the interval.
     *
     * @return std::string: Name of the interval.
     */
    std::string getIntervalName();
private:
    /*
     * Renders weekly graph for given temperature and humidity values.
     *
     * @param temp: Vector of temperature values. It should contain 4 values, one for each week of the month.
     *              If the value is -404 it means that measurement for that week is missing.
     * @param hum:  Vector of humidity values. It should contain 4 values, one for each week of the month.
     *              If the value is -404 it means that measurement for that week is missing.
     */
    void renderWeeklyGraph(const std::vector<float>& temp, const std::vector<float>& hum);

    /*
     * Gets weekly temperature and humidity values from the file.
     *
     * @param temp: Vector where the temperature values will be stored.
     * @param hum: Vector where the humidity values will be stored.
     * @param sensor: Sensor for which the values should be retrieved.
     */
    void getWeeklyValuesFromFile(std::vector<float>& temp, std::vector<float>& hum, Sensor* sensor);

    /*
     * Generates weekly temperature and humidity values for the given date.
     *
     * @param temp: Vector where the temperature values will be stored.
     * @param hum: Vector where the humidity values will be stored.
     * @param sensor: Sensor for which the values should be generated.
     * @param date: Date for which the values should be generated.
     */
    void generateWeeklyValues(std::vector<float>& temp, std::vector<float>& hum, Sensor* sensor, datetime_t date);
};

#endif //PICO_BOILERPLATE_CONCRETE_STRATEGY_WEEKLY_H

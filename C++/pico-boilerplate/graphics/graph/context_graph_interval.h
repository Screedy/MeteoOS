//
// Created by Petr Jurásek on 06.07.2024.
//

#ifndef PICO_BOILERPLATE_CONTEXT_GRAPH_INTERVAL_H
#define PICO_BOILERPLATE_CONTEXT_GRAPH_INTERVAL_H

#include <string>
#include <memory>
#include <string.h>

#include "strategy_graph_interval.h"
#include "../../sensors/Sensor.h"
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

/*
 * A singleton class that holds the strategy to render the graph for a given time interval.
 */
class ContextGraphInterval {
public:
    /*
     * Constructor that sets the strategy to render the graph.
     *
     * @param strategy: Strategy to render the graph.
     * @see StrategyGraphInterval
     * @see ConcreteStrategyDaily
     * @see ConcreteStrategyWeekly
     */
    explicit ContextGraphInterval(std::unique_ptr<StrategyGraphInterval> strategy);

    /*
     * Sets the strategy to render the graph.
     *
     * @param strategy: Strategy to render the graph.
     * @see StrategyGraphInterval
     * @see ConcreteStrategyDaily
     * @see ConcreteStrategyWeekly
     */
    void setStrategy(std::unique_ptr<StrategyGraphInterval> strategy);

    /*
     * Renders the graph for the given date and sensor.
     *
     * @param date: Date for which the graph should be rendered.
     * @param sensor: Sensor for which the graph should be rendered.
     * @param force_redraw: If true, the graph will be redrawn even if it was already rendered for the given date.
     */
    void renderGraph(datetime_t date, Sensor* sensor, bool force_redraw);
private:

    /*
     * Strategy to render the graph with. It is a unique pointer to the StrategyGraphInterval child class.
     */
    std::unique_ptr<StrategyGraphInterval> _strategy;
};

#endif //PICO_BOILERPLATE_CONTEXT_GRAPH_INTERVAL_H

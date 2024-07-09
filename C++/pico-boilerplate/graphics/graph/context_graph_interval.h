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
    explicit ContextGraphInterval(std::unique_ptr<StrategyGraphInterval> strategy);
    void setStrategy(std::unique_ptr<StrategyGraphInterval> strategy);
    void renderGraph(datetime_t date, Sensor* sensor, bool force_redraw);
private:
    std::unique_ptr<StrategyGraphInterval> _strategy;
};

#endif //PICO_BOILERPLATE_CONTEXT_GRAPH_INTERVAL_H

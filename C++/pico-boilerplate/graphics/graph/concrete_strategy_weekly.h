//
// Created by Petr Jurásek on 06.07.2024.
//

#ifndef PICO_BOILERPLATE_CONCRETE_STRATEGY_WEEKLY_H
#define PICO_BOILERPLATE_CONCRETE_STRATEGY_WEEKLY_H

#include "strategy_graph_interval.h"

class ConcreteStrategyWeekly : public StrategyGraphInterval {
public:
    void renderGraph(datetime_t date, Sensor* sensor, bool force_redraw) override;
};

#endif //PICO_BOILERPLATE_CONCRETE_STRATEGY_WEEKLY_H

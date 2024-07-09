//
// Created by Petr Jurásek on 06.07.2024.
//

#ifndef PICO_BOILERPLATE_CONCRETE_STRATEGY_DAILY_H
#define PICO_BOILERPLATE_CONCRETE_STRATEGY_DAILY_H

#include <vector>
#include "strategy_graph_interval.h"

class ConcreteStrategyDaily : public StrategyGraphInterval {
public:
    void renderGraph(datetime_t date, Sensor* sensor, bool force_redraw) override;
private:
    void renderDailyGraph(const std::vector<float>& temp, const std::vector<float>& hum);

};

#endif //PICO_BOILERPLATE_CONCRETE_STRATEGY_DAILY_H

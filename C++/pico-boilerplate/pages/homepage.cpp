//
// Created by Petr Jurásek on 04.08.2024.
//

#include "homepage.h"

bool was_rendered = false;

void render_homepage(int graph_interval, datetime_t* last_graph_rendered){
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();

    clear_fast();
    graphics.set_pen(Colors::WHITE);

    render_homepage_buttons(graph_interval);
    render_nav_arrows(6);
    render_sensor_details();
    render_thick_separator();

    // If time is set and the difference between the last graph rendered and the current time is greater than 2 minutes
    bool time_set = is_rtc_set();
    datetime_t time_before_graph;
    rtc_get_datetime(&time_before_graph);
    int diff = time_before_graph.min - last_graph_rendered->min;

    if (time_set){
        // Get the current active sensor
        SensorManager& sensor_manager = SensorManager::getInstance();
        Sensor* active_sensor = sensor_manager.getSensor(sensor_manager.getActiveSensor());

        // Set the strategy for the graph interval
        std::unique_ptr<StrategyGraphInterval> strategy;
        if (graph_interval == GraphInterval::DAILY){
            strategy = std::make_unique<ConcreteStrategyDaily>();
        } else if (graph_interval == GraphInterval::WEEKLY){
            strategy = std::make_unique<ConcreteStrategyWeekly>();
        } else if (graph_interval == GraphInterval::MONTHLY){
            // strategy = std::make_unique<ConcreteStrategyMonthly>();
        }

        if (graph_interval != GraphInterval::MONTHLY){
            ContextGraphInterval setStrategy(std::move(strategy));
            setStrategy.renderGraph(get_current_datetime(), active_sensor, false);
        }

        was_rendered = true;
        rtc_get_datetime(last_graph_rendered);
    } else {
        graphics.set_pen(Colors::RED);
        graphics.text("NO GRAPH", Point{120, DISPLAY_HEIGHT/2-10}, 250, 2);
    }

    driver.update(&graphics);
}
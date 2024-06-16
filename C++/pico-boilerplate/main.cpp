#include "pico/stdlib.h"

#include <string.h>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <stdio.h>

#include "config/config.h"
#include "config/Display.h"
#include "graphics/graphics.h"
#include "graphics/page_elements.h"
#include "sensors/DHT11.h"
#include "sensors/SensorManager.h"
#include "pages/Settings.h"

using namespace pimoroni;


Display& display = Display::getInstance();
auto& driver = display.getDriver();
auto& graphics = display.getGraphics();
auto& Buttons = Buttons::getInstance();
auto& sensor_manager = SensorManager::getInstance();

void render_homepage(int graph_interval){

    clear_fast();
    graphics.set_pen(Colors::WHITE);

    render_homepage_buttons(graph_interval);
    render_nav_arrows(6);
    render_sensor_details();

    graphics.line(Point{100, 16}, Point{100, 120});
    graphics.line(Point{101, 16}, Point{101, 120});
    graphics.line(Point{102, 16}, Point{102, 120});

    //auto active_sensor = sensor_manager.sensors[sensor_manager.active_sensor];
    //graph.render_graph(//TODO: graph_interval, active_sensor);

    driver.update(&graphics);
}

int main() {
    stdio_init_all();

    int graph_interval = GraphInterval::DAILY;

    graphics.set_pen(Colors::WHITE);
    graphics.clear();

    auto& sensor1 = sensor_manager.getSensor(0);

    while(true){
        if (Buttons.is_button_x_pressed()){
            //TODO: change the graph interval

            if (graph_interval == GraphInterval::DAILY){
                graph_interval = GraphInterval::WEEKLY;
            } else if (graph_interval == GraphInterval::WEEKLY){
                graph_interval = GraphInterval::MONTHLY;
            } else if (graph_interval == GraphInterval::MONTHLY){
                graph_interval = GraphInterval::DAILY;
            }
        } else if (Buttons.is_button_y_pressed()){
            printf("Opening menu\n");
            settings_loop();
            printf("Menu closed\n");
        } else if (Buttons.is_button_a_pressed()){
            printf("Button A pressed\n");
            //TODO: Next sensor
        } else if (Buttons.is_button_b_pressed()){
            printf("Button B pressed\n");
            //TODO: Previous sensor
        }

        render_homepage(graph_interval);

        auto err = sensor1->read();
        if (err != 0){
            printf("Error reading sensor\n");
            printf("Error code: %d\n", err);
            continue;
        }
        //printf("Temperature: %f\n", sensor1->getTemperature());
        //printf("Humidity: %f\n", sensor1->getHumidity());
        printf("Sensor1 temp: %f, hum: %f\n", sensor1->getTemperature(), sensor1->getHumidity());

        sleep_ms(300);
    }

    return 0;
}
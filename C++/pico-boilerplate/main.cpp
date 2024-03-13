#include "pico/stdlib.h"

#include <string.h>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <stdio.h>

//#include "config/globals.h"
#include "config/config.h"
#include "config/Display.h"
#include "graphics/graphics.h"

//#include "rgbled.hpp"

using namespace pimoroni;

//Display& display = Display::get_instance();
//ST7789& st7789 = *display.get_display();
//PicoGraphics_PenRGB332& graphics = *display.get_graphics();


Display& display = Display::getInstance();
auto& driver = display.getDriver();
auto& graphics = display.getGraphics();

Buttons Buttons;

void render_homepage(){

    clear_fast();
    graphics.set_pen(Colors::WHITE);

    //render_homepage_buttons(graph_interval;
    //render_nav_arrows(6);
    //render_sensor_details();
    graphics.line({101, 16}, {120, 3});

    //auto active_sensor = sensor_manager.sensors[sensor_manager.active_sensor];
    //graph.render_graph(//TODO: graph_interval, active_sensor);

    graphics.update();
}

int main() {


    stdio_init_all();

    pimoroni::Point p1 = {0, 0};
    pimoroni::Point p2 = {240, 240};

    graphics.set_pen(0, 0, 0);
    graphics.clear();

    while(true){
        if (Buttons.is_button_x_pressed()){
            graphics.set_pen(0, 255, 0);
            //TODO: change the graph interval
        } else if (Buttons.is_button_y_pressed()){
            printf("Opening menu\n");
            graphics.set_pen(255, 0, 0);
            printf("Menu closed\n");
        } else if (Buttons.is_button_a_pressed()){
            printf("Button A pressed\n");
            graphics.set_pen(0, 0, 255);
        } else if (Buttons.is_button_b_pressed()){
            printf("Button B pressed\n");
        }

        //graphics.set_pen(0, 0, 0);
        //graphics.clear();
        //graphics.set_pen(255, 0, 0);
        graphics.line(p1, p2);
        draw_clock(120, 120);
        driver.update(&graphics);
        sleep_ms(1000);
    }

    return 0;
}
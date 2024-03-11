#include "pico/stdlib.h"

#include <string.h>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <stdio.h>

#include "config/config.h"
#include "config/Display.h"

//#include "rgbled.hpp"

using namespace pimoroni;

Display& display = Display::get_instance();
ST7789& st7789 = *display.get_display();
PicoGraphics_PenRGB332& graphics = *display.get_graphics();
Buttons Buttons;

void render_homepage(){

}

int main() {
    stdio_init_all();

    //st7789.set_backlight(100);

    Point p1 = {0, 0};
    Point p2 = {100, 100};
    while(true){
        if (Buttons.is_button_x_pressed()){
            //TODO: change the graph interval
        } else if (Buttons.is_button_y_pressed()){
            printf("Opening menu\n");

            printf("Menu closed\n");
        } else if (Buttons.is_button_a_pressed()){
            printf("Button A pressed\n");
        } else if (Buttons.is_button_b_pressed()){
            printf("Button B pressed\n");
        }


        graphics.set_pen(0, 0, 0);
        graphics.clear();
        graphics.set_pen(255, 0, 0);
        graphics.line(p1, p2);
        st7789.update(&graphics);
        sleep_ms(1000);
    }

    return 0;
}
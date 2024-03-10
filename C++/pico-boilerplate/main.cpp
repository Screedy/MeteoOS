#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "pico_display.hpp"
#include "pico/stdlib.h"

#include <string.h>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <stdio.h>

#include "config/config.h"

//#include "rgbled.hpp"

using namespace pimoroni;

ST7789 st7789(PicoDisplay::WIDTH, PicoDisplay::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

Buttons Buttons;

int main() {
    stdio_init_all();

    st7789.set_backlight(100);

    Point p1 = {0, 0};
    Point p2 = {100, 100};
    while(true){
        if (Buttons.is_button_a_pressed()) {
            p1.x += 10;
        } else {
            p1.x = 0;
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
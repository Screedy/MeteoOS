//
// Created by Petr Jurásek on 13.03.2024.
//

#ifndef PICO_BOILERPLATE_DISPLAY_H
#define PICO_BOILERPLATE_DISPLAY_H

#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "pico_display.hpp"
#include "pico/stdlib.h"

using namespace pimoroni;

class Display {
public:
    static Display& getInstance();
    ST7789& getDriver();
    PicoGraphics_PenRGB332& getGraphics();
    Display(const Display&) = delete;
    Display& operator=(const Display&) = delete;
private:
    Display();
    ST7789 st7789;
    PicoGraphics_PenRGB332 graphics;
};

#endif //PICO_BOILERPLATE_DISPLAY_H

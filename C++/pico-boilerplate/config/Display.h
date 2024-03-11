//
// Created by Petr Jurásek on 11.03.2024.
//

#ifndef PICO_BOILERPLATE_DISPLAY_H
#define PICO_BOILERPLATE_DISPLAY_H

#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "pico_display.hpp"

using namespace pimoroni;

/*
 * The Display singleton class is responsible for managing the only display object in the system.
 * It is a wrapper around the Pimoroni PicoDisplay library.
 */
class Display {
private:
    ST7789 st7789;
    PicoGraphics_PenRGB332 graphics;

    Display();

    Display(const Display&) = delete;
    Display& operator=(const Display&) = delete;

public:
    static Display& get_instance();
    ST7789* get_display();
    PicoGraphics_PenRGB332* get_graphics();
};

#endif //PICO_BOILERPLATE_DISPLAY_H

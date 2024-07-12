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

/*
 * Singleton class for managing the display. It provides access to the ST7789 driver and PicoGraphics library.
 * The display is initialized in the constructor.
 */
class Display {
public:
    /*
     * The getter for the singleton instance of the Display class.
     *
     * @return The singleton instance of the Display class.
     */
    static Display& getInstance();

    /*
     * The getter for the ST7789 driver.
     *
     * @return The ST7789 driver.
     */
    ST7789& getDriver();

    /*
     * The getter for the PicoGraphics library.
     *
     * @return The PicoGraphics library. In this case, the PicoGraphics_PenRGB332 class.
     */
    PicoGraphics_PenRGB332& getGraphics();

    Display(const Display&) = delete;
    Display& operator=(const Display&) = delete;
private:
    /*
     * The constructor that initializes the display. It initializes the ST7789 driver and the PicoGraphics library.
     */
    Display();

    /*
     * The ST7789 driver. It is used for controlling the display.
     */
    ST7789 st7789;

    /*
     * The PicoGraphics library. It is used for drawing on the display and refreshing the display.
     */
    PicoGraphics_PenRGB332 graphics;
};

#endif //PICO_BOILERPLATE_DISPLAY_H

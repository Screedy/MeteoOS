//
// Created by Petr Jurásek on 11.03.2024.
//

#include "Display.h"

Display& Display::get_instance() {
    static Display instance;
    return instance;
}

Display::Display()
    :st7789(PicoDisplay::WIDTH, PicoDisplay::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT)),
    graphics(st7789.width, st7789.height, nullptr) {}

ST7789* Display::get_display() {
    return &st7789;
}

PicoGraphics_PenRGB332* Display::get_graphics() {
    return &graphics;
}

//
// Created by Petr Jurásek on 13.03.2024.
//

#include "Display.h"

Display::Display()
    :st7789(PicoDisplay::WIDTH, PicoDisplay::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT)),
    graphics(st7789.width, st7789.height, nullptr){}

Display& Display::getInstance() {
    static Display instance;
    return instance;
}

ST7789& Display::getDriver() {
    return st7789;
}

PicoGraphics_PenRGB332& Display::getGraphics() {
    return graphics;
}
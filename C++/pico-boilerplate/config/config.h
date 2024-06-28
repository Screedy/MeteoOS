//
// Created by Petr Jurásek on 13.03.2024.
//

#ifndef PICO_BOILERPLATE_CONFIG_H
#define PICO_BOILERPLATE_CONFIG_H

#include "pico/stdlib.h"
#include "./Display.h"
#include "drivers/st7789/st7789.hpp"

#define BUTTON_A 12
#define BUTTON_B 13
#define BUTTON_X 14
#define BUTTON_Y 15

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 135

namespace Config{
    extern Display& display;
    extern pimoroni::ST7789& driver;
    extern pimoroni::PicoGraphics_PenRGB332& graphics;
}

class Buttons {
public:
    //Buttons();

    bool is_button_a_pressed();
    bool is_button_b_pressed();
    bool is_button_x_pressed();
    bool is_button_y_pressed();

    static Buttons& getInstance();

private:
    Buttons();
};

struct Colors {
    static int WHITE;
    static int BLACK;
    static int RED;
    static int GREEN;
    static int BLUE;
    static int GRAY;
};

struct GraphInterval {
    static int DAILY;
    static int WEEKLY;
    static int MONTHLY;
};

extern std::vector<int> availablePins;

extern std::vector<std::string> sensorTypes;

#endif //PICO_BOILERPLATE_CONFIG_H

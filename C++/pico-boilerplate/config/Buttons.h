//
// Created by Petr Jurásek on 05.08.2024.
//

#ifndef PICO_BOILERPLATE_BUTTONS_H
#define PICO_BOILERPLATE_BUTTONS_H

#include "pico/stdlib.h"
#include "./Display.h"
#include "drivers/st7789/st7789.hpp"

#define BUTTON_A 12
#define BUTTON_B 13
#define BUTTON_X 14
#define BUTTON_Y 15

class Buttons {
public:
    static Buttons& getInstance();

    bool is_button_a_pressed();
    bool is_button_b_pressed();
    bool is_button_x_pressed();
    bool is_button_y_pressed();

    bool is_button_a_held();
    bool is_button_b_held();
    bool is_button_x_held();
    bool is_button_y_held();

private:
    Buttons();
    bool debounce_button(uint gpio, bool& last_state);

    bool button_a_last_state;
    bool button_b_last_state;
    bool button_x_last_state;
    bool button_y_last_state;

    absolute_time_t last_a_pressed_time;
    absolute_time_t last_b_pressed_time;
    absolute_time_t last_x_pressed_time;
    absolute_time_t last_y_pressed_time;
};

#endif //PICO_BOILERPLATE_BUTTONS_H

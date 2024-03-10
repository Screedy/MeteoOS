//
// Created by Petr Jurásek on 10.03.2024.
//

#ifndef PICO_BOILERPLATE_CONFIG_H
#define PICO_BOILERPLATE_CONFIG_H

#include "pico/stdlib.h"

#define BUTTON_A 12
#define BUTTON_B 13
#define BUTTON_X 14
#define BUTTON_Y 15

class Buttons {
public:
    Buttons();

    bool is_button_a_pressed();
    bool is_button_b_pressed();
    bool is_button_x_pressed();
    bool is_button_y_pressed();
};

#endif //PICO_BOILERPLATE_CONFIG_H

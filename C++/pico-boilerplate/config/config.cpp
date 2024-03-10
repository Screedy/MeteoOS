//
// Created by Petr Jurásek on 10.03.2024.
//

#include "config.h"


Buttons::Buttons() {
    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_init(BUTTON_X);
    gpio_init(BUTTON_Y);

    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_set_dir(BUTTON_X, GPIO_IN);
    gpio_set_dir(BUTTON_Y, GPIO_IN);

    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);
    gpio_pull_up(BUTTON_X);
    gpio_pull_up(BUTTON_Y);
}

bool Buttons::is_button_a_pressed() {
    return !gpio_get(BUTTON_A);
}

bool Buttons::is_button_b_pressed() {
    return !gpio_get(BUTTON_B);
}

bool Buttons::is_button_x_pressed() {
    return !gpio_get(BUTTON_X);
}

bool Buttons::is_button_y_pressed() {
    return !gpio_get(BUTTON_Y);
}
//
// Created by Petr Jurásek on 05.08.2024.
//

#include "Buttons.h"

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

    button_a_last_state = true;
    button_b_last_state = true;
    button_x_last_state = true;
    button_y_last_state = true;

    last_a_pressed_time = make_timeout_time_ms(0);
    last_b_pressed_time = make_timeout_time_ms(0);
    last_x_pressed_time = make_timeout_time_ms(0);
    last_y_pressed_time = make_timeout_time_ms(0);
}

bool Buttons::debounce_button(uint gpio, bool& last_state) {
    bool current_state = !gpio_get(gpio);
    bool pressed = false;

    if (current_state && !last_state) {
        pressed = true;
    }

    last_state = current_state;
    return pressed;
}

bool Buttons::is_button_a_pressed() {
    return debounce_button(BUTTON_A, button_a_last_state);
}

bool Buttons::is_button_b_pressed() {
    return debounce_button(BUTTON_B, button_b_last_state);
}

bool Buttons::is_button_x_pressed() {
    return debounce_button(BUTTON_X, button_x_last_state);
}

bool Buttons::is_button_y_pressed() {
    return debounce_button(BUTTON_Y, button_y_last_state);
}

bool Buttons::is_button_a_held() {
    if (!gpio_get(BUTTON_A)) {
        absolute_time_t now = get_absolute_time();
        if (absolute_time_diff_us(last_a_pressed_time, now) >= 300*1000) {
            last_a_pressed_time = now;
            return true;
        }
    }
    return false;
}

bool Buttons::is_button_b_held() {
    if (!gpio_get(BUTTON_B)) {
        absolute_time_t now = get_absolute_time();
        if (absolute_time_diff_us(last_b_pressed_time, now) >= 300*1000) {
            last_b_pressed_time = now;
            return true;
        }
    }
    return false;
}

bool Buttons::is_button_x_held() {
    if (!gpio_get(BUTTON_X)) {
        absolute_time_t now = get_absolute_time();
        if (absolute_time_diff_us(last_x_pressed_time, now) >= 300*1000) {
            last_x_pressed_time = now;
            return true;
        }
    }
    return false;
}

bool Buttons::is_button_y_held() {
    if (!gpio_get(BUTTON_Y)) {
        absolute_time_t now = get_absolute_time();
        if (absolute_time_diff_us(last_y_pressed_time, now) >= 300*1000) {
            last_y_pressed_time = now;
            return true;
        }
    }
    return false;
}

Buttons& Buttons::getInstance() {
    static Buttons instance;
    return instance;
}
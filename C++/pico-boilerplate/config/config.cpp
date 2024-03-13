//
// Created by Petr Jurásek on 13.03.2024.
//

#include "config.h"

using namespace Config;

namespace Config{
    Display& display = Display::getInstance();
    pimoroni::ST7789& driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332& graphics = display.getGraphics();
}

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

int Colors::WHITE = graphics.create_pen(255, 255, 255);
int Colors::BLACK = graphics.create_pen(0, 0, 0);
int Colors::RED = graphics.create_pen(255, 0, 0);
int Colors::GREEN = graphics.create_pen(0, 255, 0);
int Colors::BLUE = graphics.create_pen(0, 0, 255);
int Colors::GRAY = graphics.create_pen(128, 128, 128);
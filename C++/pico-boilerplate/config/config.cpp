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

    button_a_last_state = true;
    button_b_last_state = true;
    button_x_last_state = true;
    button_y_last_state = true;
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
    return !gpio_get(BUTTON_A);
}

bool Buttons::is_button_b_held() {
    return !gpio_get(BUTTON_B);
}

bool Buttons::is_button_x_held() {
    return !gpio_get(BUTTON_X);
}

bool Buttons::is_button_y_held() {
    return !gpio_get(BUTTON_Y);
}

Buttons& Buttons::getInstance() {
    static Buttons instance;
    return instance;
}

int Colors::WHITE = graphics.create_pen(255, 255, 255);
int Colors::BLACK = graphics.create_pen(0, 0, 0);
int Colors::RED = graphics.create_pen(255, 0, 0);
int Colors::GREEN = graphics.create_pen(0, 255, 0);
int Colors::BLUE = graphics.create_pen(0, 0, 255);
int Colors::GRAY = graphics.create_pen(128, 128, 128);

int GraphInterval::DAILY = 0;
int GraphInterval::WEEKLY = 1;
int GraphInterval::MONTHLY = 2;

std::vector<int> availablePins = {0, 1, 2, 3, 4, 5, 21, 22, 26, 27, 28};

std::vector<std::string> sensorTypes = {"DHT11", "DS18B20"};
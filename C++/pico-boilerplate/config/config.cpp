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
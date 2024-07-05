//
// Created by Petr Jurásek on 13.03.2024.
//

#include "graphics.h"

namespace Graphics{
    Display& display = Display::getInstance();
    pimoroni::ST7789& driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332& graphics = display.getGraphics();
}

using namespace Graphics;

pimoroni::Point rotate_point(pimoroni::Point rotatedPoint, pimoroni::Point center, int angle) {
    pimoroni::Point result;

    int x = rotatedPoint.x;
    int y = rotatedPoint.y;
    int cx = center.x;
    int cy = center.y;
    float rad = angle * M_PI / 180;
    int new_x = (int) (cos(rad) * (x - cx) - sin(rad) * (y - cy) + cx);
    int new_y = (int) (sin(rad) * (x - cx) + cos(rad) * (y - cy) + cy);
    result = pimoroni::Point{new_x, new_y};
    return result;
}

std::array<pimoroni::Point, 3> createTriangle(int x, int y, int size){
    std::array<pimoroni::Point, 3> triangle = {
            pimoroni::Point{x, y},
            pimoroni::Point{x + size, y},
            pimoroni::Point{x + size / 2, y + size}
    };
    return triangle;
}

void draw_arrow(int x, int y, int size, int direction){
    graphics.set_pen(Colors::WHITE);
    auto triangle = createTriangle(x, y, size);
    for (int i = 0; i < 3; i++){
        triangle[i] = rotate_point(triangle[i], pimoroni::Point{x + size / 2, y + size / 2}, direction);
    }

    graphics.triangle(pimoroni::Point{triangle[0].x, triangle[0].y},
                      pimoroni::Point{triangle[1].x, triangle[1].y},
                      pimoroni::Point{triangle[2].x, triangle[2].y});
}

void draw_empty_circle(int x, int y, int radius){
    graphics.set_pen(Colors::WHITE);
    graphics.circle({x, y}, radius);
    graphics.set_pen(Colors::BLACK);
    graphics.circle({x, y}, radius - 1);
}

void draw_clock(int x, int y){
    draw_empty_circle(x, y, 10);
    draw_empty_circle(x, y, 9);
    graphics.set_pen(Colors::WHITE);
    graphics.line({x, y}, {x, y - 7});
    graphics.line({x, y}, {x + 4, y});
}

void draw_thermometer(int x, int y){
    draw_empty_circle(x, y + 5, 5);

    graphics.line({x - 2, y}, {x + 3, y});
    graphics.set_pen(Colors::WHITE);
    graphics.line({x, y - 6}, {x, y + 5});

    graphics.line({x - 2, y + 1}, {x - 2, y - 7});
    graphics.line({x + 2, y + 1}, {x + 2, y - 7});

    graphics.pixel({x - 1, y - 8});
    graphics.pixel({x + 1, y - 8});

    graphics.pixel({x, y - 9});

    graphics.circle({x, y + 5}, 2);

    graphics.line({x + 5, y - 8}, {x + 8, y - 8});
    graphics.line({x + 5, y - 6}, {x + 7, y - 6});
    graphics.line({x + 5, y - 4}, {x + 8, y - 4});
    graphics.line({x + 5, y - 2}, {x + 7, y - 2});
}

void draw_humidity(int x, int y){
    graphics.set_pen(Colors::WHITE);
    graphics.line({x, y - 9}, {x, y + 9});

    graphics.line({x - 1, y - 7}, {x - 1, y + 9});
    graphics.line({x - 2, y - 4}, {x - 2, y + 9});
    graphics.line({x - 3, y - 2}, {x - 3, y + 8});
    graphics.line({x - 4, y}, {x - 4, y + 7});
    graphics.line({x - 5, y + 1}, {x - 5, y + 6});

    graphics.line({x + 1, y - 7}, {x + 1, y + 9});
    graphics.line({x + 2, y - 4}, {x + 2, y + 9});
    graphics.line({x + 3, y - 2}, {x + 3, y + 8});
    graphics.line({x + 4, y}, {x + 4, y + 7});
    graphics.line({x + 5, y + 1}, {x + 5, y + 6});
}

void clear_fast(){
    graphics.set_pen(Colors::BLACK);
    graphics.clear();
}

void draw_next(){
    graphics.set_pen(Colors::GREEN);
    graphics.text("NEXT", Point{DISPLAY_WIDTH - 45, 20}, 200, 2);
}

void draw_prev(){
    graphics.set_pen(Colors::RED);
    graphics.text("PREV", Point{DISPLAY_WIDTH - 45, DISPLAY_HEIGHT - 20}, 200, 2);
}

void draw_back(){
    graphics.set_pen(Colors::RED);
    graphics.text("BACK", pimoroni::Point{190, 115}, 250, 2);
}

void draw_ok(){
    graphics.set_pen(Colors::GREEN);
    graphics.text("OK", Point{DISPLAY_WIDTH - 30, 20}, 200, 2);
}

void draw_cancel(){
    graphics.set_pen(Colors::RED);
    graphics.text("CANCEL", Point{DISPLAY_WIDTH - 65, DISPLAY_HEIGHT - 20}, 200, 2);
}

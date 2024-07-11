//
// Created by Petr Jurásek on 13.03.2024.
//

#ifndef PICO_BOILERPLATE_GRAPHICS_H
#define PICO_BOILERPLATE_GRAPHICS_H

#include "../config/Display.h"
#include "../config/config.h"

namespace Graphics{
    extern Display& display;
    extern pimoroni::ST7789& driver;
    extern pimoroni::PicoGraphics_PenRGB332& graphics;
}

/*
 * Rotates a point around the center point with a given angle.
 *
 * @param point The point to rotate. This is a tuple <x, y>.
 * @param center The center of rotation. This is a tuple <x, y>.
 * @param angle The angle of rotation in degrees.
 * @return The rotated point. This is a tuple <x, y>.
 */
pimoroni::Point rotate_point(pimoroni::Point rotatedPoint, pimoroni::Point center, int angle);

/*
 * Creates a triangle with the given size and position. This function returns
 * a sequence of points that represent the triangle.
 *
 * @param x The x coordinate of the triangle.
 * @param y The y coordinate of the triangle.
 * @param size The size of the triangle.
 * @return A sequence of points that represent the triangle.
 */
std::array<pimoroni::Point, 3> createTriangle(int x, int y, int size);

/*
 * Draws an arrow on the display.
 *
 * @param x The x coordinate of the arrow.
 * @param y The y coordinate of the arrow.
 * @param size The size of the arrow.
 * @param direction The direction of the arrow. This is an angle in degrees.
 * @return None
 *
 * Example:
 * @code
 * draw_arrow(50, 50, 10, 0); // Draws an arrow pointing to the right.
 * draw_arrow(50, 50, 10, 90); // Draws an arrow pointing up.
 * @endcode
 */
void draw_arrow(int x, int y, int size, int direction);

/*
 * Draws an empty circle on the display.
 * @param x The x coordinate of the circle.
 * @param y The y coordinate of the circle.
 * @param radius The radius of the circle.
 * return None
 */
void draw_empty_circle(int x, int y, int radius);

/*
 * Draws a clock icon on the display.
 *
 * @param x The x coordinate of the clock.
 * @param y The y coordinate of the clock.
 * @return None
 */
void draw_clock(int x, int y);

/*
 * Draws a thermometer icon on the display.
 *
 * @param x The x coordinate of the thermometer.
 * @param y The y coordinate of the thermometer.
 * @return None
 */
void draw_thermometer(int x, int y);

/*
 * Draws a humidity icon on the display.
 *
 * @param x The x coordinate of the humidity.
 * @param y The y coordinate of the humidity.
 * @return None
 */
void draw_humidity(int x, int y);

/*
 * Clears the display without refreshing the display to remove flickering.
 * @return None
 */
void clear_fast();

void draw_next();
void draw_prev();
void draw_back();
void draw_ok();
void draw_confirm();
void draw_cancel();

#endif //PICO_BOILERPLATE_GRAPHICS_H

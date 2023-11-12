import main

display = main.display


def rotate_point(param, param1, direction):
    """Rotates a point around a given point with a given angle.

    :param param: The point to rotate.
    :param param1: The point to rotate around.
    :param direction: The direction to rotate in. 0 is up, 90 is right, 180 is down, 270 is left.
    :return: The rotated point as an integer tuple.

    credit: https://stackoverflow.com/a/34374437
    """

    from math import cos, sin, radians

    x, y = param
    cx, cy = param1
    angle = radians(direction)
    return int(cx + cos(angle) * (x - cx) - sin(angle) * (y - cy)), int(cy + sin(angle) * (x - cx) + cos(angle) * (y -
                                                                                                                   cy))


def draw_arrow(x: int, y: int, size: int, direction: int):
    """Draws an arrow on the display with 360-degree rotation.

    :param x: The x coordinate of the arrow.
    :param y: The y coordinate of the arrow.
    :param size: The size of the arrow.
    :param direction: The direction of the arrow. 0 is up, 90 is right, 180 is down, 270 is left.
    :return: None
    """

    display.set_pen(main.WHITE)
    triangle = [(x, y), (x + size, y), (x + size / 2, y + size)]
    for i in range(len(triangle)):
        triangle[i] = rotate_point(triangle[i], (x + size / 2, y + size / 2), direction)
    display.triangle(triangle[0][0], triangle[0][1], triangle[1][0], triangle[1][1], triangle[2][0], triangle[2][1])


def draw_empty_circle(x: int, y: int, radius: int):
    """Draws an empty circle on the display. With x and y being the center of the circle.

    :param x: The x coordinate of the middle of the circle.
    :param y: The y coordinate of the middle of the circle.
    :param radius: The radius of the circle.
    :return: None
    """

    display.set_pen(main.WHITE)
    display.circle(x, y, radius)
    display.set_pen(main.BLACK)
    display.circle(x, y, radius - 1)


def draw_sd_card(x: int, y: int, connected: bool = True):
    """Draws an SD card icon on the display.

    :param x: The x coordinate of the SD card.
    :param y: The y coordinate of the SD card.
    :param connected: Whether the SD card is connected or not. If not, a red line will be drawn.
    :return: None
    """

    display.set_pen(main.WHITE)

    display.line(x+2, y, x+8, y)
    display.line(x+8, y, x+8, y+10)
    display.line(x+8, y+10, x, y+10)
    display.line(x, y+10, x, y+7)
    display.line(x, y+7, x+2, y+6)
    display.line(x+2, y+6, x+2, y+4)
    display.line(x+2, y+4, x, y+4)
    display.line(x, y+4, x, y+2)
    display.line(x, y+2, x+2, y)

    if not connected:
        display.set_pen(main.RED)
        display.line(x-3, y+12, x+11, y-2)


def draw_clock(x: int, y: int):
    """Draws a clock icon on the display.

    :param x: The x coordinate of the clock.
    :param y: The y coordinate of the clock.
    :return: None
    """

    draw_empty_circle(x+5, y+5, 5)
    display.set_pen(main.WHITE)
    display.line(x+5, y+5, x+5, y+3)
    display.line(x+5, y+5, x+8, y+5)


def draw_thermometer(x: int, y: int):
    """Draws a thermometer icon on the display.

    :param x: The x coordinate of the thermometer.
    :param y: The y coordinate of the thermometer.
    :return: None
    """

    # Base of thermometer
    display.set_pen(main.WHITE)
    display.circle(x+5, y+5, 3)
    display.set_pen(main.BLACK)
    display.circle(x+5, y+5, 2)
    display.set_pen(main.WHITE)
    display.circle(x+5, y+5, 1)

    # Upper dome of thermometer
    display.circle(x+5, y-3, 2)
    display.set_pen(main.BLACK)
    display.circle(x+5, y-3, 1)
    display.rectangle(x+4, y-2, 2, 3)

    # Thermometer line
    display.set_pen(main.WHITE)
    display.line(x+5, y+5, x+5, y-3)

    # Thermometer side lines
    display.set_pen(main.BLACK)
    display.line(x+4, y+4, x+4, y-4)
    display.line(x+6, y+4, x+6, y-4)
    display.set_pen(main.WHITE)
    display.line(x+3, y+4, x+3, y-4)
    display.line(x+7, y+4, x+7, y-4)

    # Lines on the side
    display.line(x+9, y+2, x+11, y+2)
    display.line(x+9, y, x+10, y)
    display.line(x+9, y-2, x+11, y-2)


def draw_humidity(x: int, y: int):
    """Draws a humidity icon on the display.

    :param x: The x coordinate of the humidity.
    :param y: The y coordinate of the humidity.
    :return: None
    """

    draw_empty_circle(x+5, y+5, 5)
    display.set_pen(main.WHITE)
    display.text("H", x+3, y+2, 240, 1)


if __name__ == "__main__":
    display.clear()
    draw_arrow(10, 10, 10, 0)
    draw_arrow(30, 10, 10, 180)
    draw_sd_card(10, 30, True)
    draw_sd_card(30, 30, False)
    draw_clock(10, 50)
    draw_thermometer(30, 50)
    draw_humidity(50, 50)
    display.update()

from config.config import Colors, Display


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
    return (int(cx + cos(angle) * (x - cx) - sin(angle) * (y - cy)),
            int(cy + sin(angle) * (x - cx) + cos(angle) * (y - cy)))


def draw_arrow(x: int, y: int, size: int, direction: int):
    """Draws an arrow on the display with 360-degree rotation.

    :param x: The x coordinate of the arrow.
    :param y: The y coordinate of the arrow.
    :param size: The size of the arrow.
    :param direction: The direction of the arrow. 0 is up, 90 is right, 180 is down, 270 is left.
    :return: None
    """

    disp = Display()

    disp().set_pen(Colors.WHITE)
    triangle = [(x, y), (x + size, y), (x + size / 2, y + size)]
    for i in range(len(triangle)):
        triangle[i] = rotate_point(triangle[i], (x + size / 2, y + size / 2), direction)
    disp().triangle(triangle[0][0], triangle[0][1], triangle[1][0], triangle[1][1], triangle[2][0], triangle[2][1])


def draw_empty_circle(x: int, y: int, radius: int):
    """Draws an empty circle on the display. With x and y being the center of the circle.

    :param x: The x coordinate of the middle of the circle.
    :param y: The y coordinate of the middle of the circle.
    :param radius: The radius of the circle.
    :return: None
    """

    disp = Display()

    disp().set_pen(Colors.WHITE)
    disp().circle(x, y, radius)
    disp().set_pen(Colors.BLACK)
    disp().circle(x, y, radius - 1)


def draw_sd_card(x: int, y: int, connected: bool = True):
    """Draws an SD card icon on the display.

    :param x: The x coordinate of the SD card.
    :param y: The y coordinate of the SD card.
    :param connected: Whether the SD card is connected or not. If not, a red line will be drawn.
    :return: None
    """

    disp = Display()

    disp().set_pen(Colors.WHITE)

    disp().line(x + 2, y, x + 8, y)
    disp().line(x + 8, y, x + 8, y + 10)
    disp().line(x + 8, y + 10, x, y + 10)
    disp().line(x, y + 10, x, y + 7)
    disp().line(x, y + 7, x + 2, y + 6)
    disp().line(x + 2, y + 6, x + 2, y + 4)
    disp().line(x + 2, y + 4, x, y + 4)
    disp().line(x, y + 4, x, y + 2)
    disp().line(x, y + 2, x + 2, y)

    if not connected:
        disp().set_pen(Colors.RED)
        disp().line(x - 3, y + 12, x + 11, y - 2)


def draw_clock(x: int, y: int):
    """Draws a clock icon on the display.

    :param x: The x coordinate of the clock.
    :param y: The y coordinate of the clock.
    :return: None
    """

    disp = Display()

    draw_empty_circle(x, y, 10)
    draw_empty_circle(x, y, 9)
    disp().set_pen(Colors.WHITE)
    disp().line(x, y, x, y - 7)
    disp().line(x, y, x + 4, y)


def draw_thermometer(x: int, y: int):
    """Draws a thermometer icon on the display.

    :param x: The x coordinate of the thermometer.
    :param y: The y coordinate of the thermometer.
    :return: None
    """

    disp = Display()

    draw_empty_circle(x, y + 5, 5)
    disp().line(x - 2, y, x + 3, y)
    disp().set_pen(Colors.WHITE)
    disp().line(x, y - 6, x, y + 5)
    disp().line(x - 2, y + 1, x - 2, y - 7)
    disp().line(x + 2, y + 1, x + 2, y - 7)
    disp().pixel(x - 1, y - 8)
    disp().pixel(x + 1, y - 8)
    disp().pixel(x, y - 9)
    disp().circle(x, y + 5, 2)
    disp().line(x + 5, y - 8, x + 8, y - 8)
    disp().line(x + 5, y - 6, x + 7, y - 6)
    disp().line(x + 5, y - 4, x + 8, y - 4)
    disp().line(x + 5, y - 2, x + 7, y - 2)


def draw_humidity(x: int, y: int):
    """Draws a humidity icon on the display.

    :param x: The x coordinate of the humidity.
    :param y: The y coordinate of the humidity.
    :return: None
    """

    disp = Display()

    disp().set_pen(Colors.WHITE)
    disp().line(x, y - 9, x, y + 9)

    disp().line(x - 1, y - 7, x - 1, y + 9)
    disp().line(x - 2, y - 4, x - 2, y + 9)
    disp().line(x - 3, y - 2, x - 3, y + 8)
    disp().line(x - 4, y, x - 4, y + 7)
    disp().line(x - 5, y + 1, x - 5, y + 6)

    disp().line(x + 1, y - 7, x + 1, y + 9)
    disp().line(x + 2, y - 4, x + 2, y + 9)
    disp().line(x + 3, y - 2, x + 3, y + 8)
    disp().line(x + 4, y, x + 4, y + 7)
    disp().line(x + 5, y + 1, x + 5, y + 6)


if __name__ == "__main__":
    display = Display()
    """
    draw_arrow(10, 10, 11, 0, dp)
    draw_arrow(30, 10, 10, 180, dp)
    draw_sd_card(10, 30, dp, True)
    draw_sd_card(30, 30, dp, False)
    draw_clock(10, 50, dp)
    draw_thermometer(30, 50, dp)
    draw_humidity(50, 50, dp)
    """
    """
    dp.set_pen(Colors.RED)
    #arrow icon square
    dp.line(5, 4, 24, 4)
    dp.line(5, 4, 5, 24)
    dp.line(5, 24, 24, 24)
    dp.line(24, 24, 24, 4)
    """
    draw_arrow(7, 7, 16, 180)

    """
    dp.set_pen(Colors.RED)
    #first icon square
    dp.line(4, 31, 24, 31)
    dp.line(4, 31, 4, 51)
    dp.line(4, 51, 24, 51)
    dp.line(24, 51, 24, 31)
    """
    draw_clock(14, 41)

    """
    dp.set_pen(Colors.RED)
    #second icon square
    dp.line(4, 58, 24, 58)
    dp.line(4, 58, 4, 78)
    dp.line(4, 78, 24, 78)
    dp.line(24, 78, 24, 58)
    """
    draw_thermometer(14, 68)

    """
    dp.set_pen(Colors.RED)
    #third icon square
    dp.line(4, 85, 24, 85)
    dp.line(4, 85, 4, 105)
    dp.line(4, 105, 24, 105)
    dp.line(24, 105, 24, 85)
    """
    draw_humidity(14, 96)

    """
    dp.set_pen(Colors.RED)
    #arrow icon square
    dp.line(4, 111, 24, 111)
    dp.line(4, 111, 4, 131)
    dp.line(4, 131, 24, 131)
    dp.line(24, 131, 24, 111)
    """
    draw_arrow(6, 113, 17, 0)

    # Texts
    # --- X was 29 before.
    # Name of sensor
    display().text("TOILET", 34, 7, 250, 2)
    # Time
    display().text("13:49", 34, 34, 250, 2)
    # Temperature
    display().text("24°C", 34, 61, 250, 2)
    # Humidity
    display().text("42%", 34, 88, 250, 2)

    # Menu button
    display().text("MENU", 190, 115, 250, 2)
    """
    dp.line(188, 115, 188, 129)
    dp.line(188, 115, 237, 115)
    dp.line(237, 115, 237, 129)
    dp.line(188, 129, 237, 129)
    """

    # Day/Week/Month button
    """
    dp.line(188, 7, 188, 21)
    dp.line(188, 7, 237, 7)
    dp.line(237, 7, 237, 21)
    dp.line(188, 21, 237, 21)
    """

    display().set_pen(Colors.WHITE)
    display().rectangle(189, 8, 13, 13)
    display().set_pen(Colors.BLACK)
    display().text("D", 190, 7, 250, 2)

    display().set_pen(Colors.BLACK)
    display().rectangle(204, 8, 13, 13)
    display().set_pen(Colors.WHITE)
    display().text("W", 205, 7, 250, 2)

    display().set_pen(Colors.BLACK)
    display().rectangle(219, 8, 13, 13)
    display().set_pen(Colors.WHITE)
    display().text("M", 220, 7, 250, 2)

    # separator
    display().set_pen(Colors.WHITE)
    display().line(101, 16, 101, 120)
    display().line(102, 16, 102, 120)
    display().line(103, 16, 103, 120)
    display().update()

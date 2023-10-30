import main

display = main.display


def rotate_point(param, param1, direction):
    """Rotates a point around a given point with a given angle.

    :param param: The point to rotate.
    :param param1: The point to rotate around.
    :param direction: The direction to rotate in. 0 is up, 90 is right, 180 is down, 270 is left.
    :return: The rotated point as a integer tuple.

    credit: https://stackoverflow.com/a/34374437
    """

    from math import cos, sin, radians

    x, y = param
    cx, cy = param1
    angle = radians(direction)
    return int(cx + cos(angle) * (x - cx) - sin(angle) * (y - cy)), int(cy + sin(angle) * (x - cx) + cos(angle) * (y - cy))


def draw_arrow(x, y, size, direction):
    """Draws an arrow on the display with 360-degree rotation.

    :param x: The x coordinate of the arrow.
    :param y: The y coordinate of the arrow.
    :param size: The size of the arrow.
    :param direction: The direction of the arrow. 0 is up, 90 is right, 180 is down, 270 is left.
    """

    display.set_pen(main.WHITE)
    triangle = [(x, y), (x + size, y), (x + size / 2, y + size)]
    for i in range(len(triangle)):
        triangle[i] = rotate_point(triangle[i], (x + size / 2, y + size / 2), direction)
    display.triangle(triangle[0][0], triangle[0][1], triangle[1][0], triangle[1][1], triangle[2][0], triangle[2][1])


if __name__ == "__main__":
    display.clear()
    draw_arrow(10, 10, 10, 0)
    draw_arrow(30, 10, 10, 180)
    display.update()

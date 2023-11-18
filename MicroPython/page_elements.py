import time

from config import Colors
from graphics import draw_arrow, draw_clock, draw_thermometer, draw_humidity
import temp_sensor


def render_nav_arrows(x: int, display, color: int = Colors.WHITE):
    """Draws navigation arrows on the screen with the given coordinates.
    Keeps the arrows height consistent across screens.

    :param x: The x coordinate of the arrows.
    :param display: The display object where the arrows will be drawn.
    :param color: The color of the arrows. Uses the pico_graphics create_pen() function to create a color.
        (Default: Colors.WHITE)
    :return: None
    """

    display.set_pen(color)
    draw_arrow(x, 20, 10, 180, display)
    draw_arrow(x, 100, 10, 0, display)


def parse_time(t):
    """Parses the given time tuple into a string.

    :param t: The time tuple to parse.
    :return: The parsed time tuple as a string.
    """

    hours = t[3]
    minutes = t[4]

    if hours < 10:
        hours = f"0{hours}"
    if minutes < 10:
        minutes = f"0{minutes}"

    return f"{hours}:{minutes}"


def render_sensor_details(x: int, display, sensor_id: int):
    """Draws the sensor details on the screen with the given coordinates.

    :param x: The x coordinate of the sensor details.
    :param display: The display object where the sensor details will be drawn.
    :param sensor_id: The sensor id of the sensor to draw the details of.
    :return: None
    """

    test_sensor = temp_sensor.DHT11(4, "test")

    display.text(test_sensor.name, x, 15, 240, 2)   # TODO: change to real sensor
    draw_clock(x, 35, display)
    current_time = time.localtime()
    display.text(parse_time(current_time), x+15, 34, 240, 2)
    draw_thermometer(x, 63, display)

    display.text(f"{test_sensor.temperature}°C", x+15, 58, 240, 2)    # TODO: draw temperature next to the thermometer
    draw_humidity(x, 85, display)
    display.text(f"{test_sensor.humidity}%", x+15, 83, 240, 2)     # TODO: draw humidity next to the humidity icon

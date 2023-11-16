from config import Colors
from graphics import draw_arrow, draw_clock, draw_thermometer, draw_humidity


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


def render_sensor_details(x: int, display, sensor_id: int):
    """Draws the sensor details on the screen with the given coordinates.

    :param x: The x coordinate of the sensor details.
    :param display: The display object where the sensor details will be drawn.
    :param sensor_id: The sensor id of the sensor to draw the details of.
    :return: None
    """

    display.text("SENS1", x, 15, 240, 2)   # TODO: draw sensor name
    draw_clock(x, 35, display)
    display.text("10:43", x+15, 34, 240, 2)   # TODO: draw time next to the clock
    draw_thermometer(x, 63, display)
    display.text("21°C", x+15, 58, 240, 2)    # TODO: draw temperature next to the thermometer
    draw_humidity(x, 85, display)
    display.text("63%", x+15, 83, 240, 2)     # TODO: draw humidity next to the humidity icon

from pimoroni import Button  # Import Buttons
from picographics import PicoGraphics  # Import universal graphics library (part of custom UF2 file)
from picographics import DISPLAY_PICO_DISPLAY  # Class for this display model
from picographics import PEN_P4  # Class for the color depth used
import time
from math import ceil
from collections import OrderedDict
import os


# import graphics_text
import graphics

display = PicoGraphics(display=DISPLAY_PICO_DISPLAY,
                       pen_type=PEN_P4,
                       rotate=0)  # Create display object

X_MAX, Y_MAX = display.get_bounds()  # 240 x 135

button_a = Button(12)
button_b = Button(13)
button_x = Button(14)
button_y = Button(15)

BLACK = display.create_pen(0, 0, 0)  # Create color black
WHITE = display.create_pen(255, 255, 255)  # Create color white
RED = display.create_pen(255, 0, 0)  # Create color red
GREEN = display.create_pen(0, 255, 0)  # Create color green


def clear_fast():
    """Clears the display without refreshing the display to remove flickering."""

    display.set_pen(BLACK)  # Set pen color to black
    display.clear()  # Clear display


def render_homepage(sensor_number, graph_interval):
    """Renders the homepage with information about the selected sensor and selected graph interval.

    :param sensor_number: The selected sensor number.
    :param graph_interval: The selected graph interval. Either 1 (Hourly), 2 (Daily), 3 (Weekly) or 4 (Monthly).
    :return: None
    """

    clear_fast()
    display.set_pen(WHITE)
    graphics.draw_arrow(10, 100, 10, 0, display)
    graphics.draw_arrow(10, 20, 10, 180, display)
    display.text("SENS1", 30, 15, 240, 2)
    graphics.draw_clock(30, 35, display)
    display.text("10:43", 45, 34, 240, 2)   # TODO: draw time next to the clock
    graphics.draw_thermometer(30, 63, display)
    display.text("21°C", 45, 58, 240, 2)    # TODO: draw temperature next to the thermometer
    graphics.draw_humidity(30, 85, display)
    display.text("63%", 45, 83, 240, 2)     # TODO: draw humidity next to the humidity icon

    display.line(100, 10, 100, 120, 2)

    display.update()

    print("Homepage rendered")


if __name__ == "__main__":
    try:
        f = open("settings.txt", "r")
        # continue with the file.
    except OSError:  # open failed (file not found)
        import setup

        setup.initial()

    try:
        fr_homepage = open("homepage_settings.txt", "r")
    except OSError:
        fw_homepage = open("homepage_settings.txt", "w")
        fw_homepage.write("0\n0")
        fw_homepage.close()
        fr_homepage = open("homepage_settings.txt", "r")

    last_sensor = int(fr_homepage.readline())
    last_graph_interval = int(fr_homepage.readline())
    fr_homepage.close()

    render_homepage(last_sensor, last_graph_interval)

    while True:
        time.sleep(.15)

        if button_x.read():
            # TODO: change the graph interval
            pass
        if button_y.read():
            # TODO: go to settings
            pass
        if button_a.read():
            # TODO: change the sensor to previous one
            pass
        if button_b.read():
            # TODO: change the sensor to next one
            pass

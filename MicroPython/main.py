from pimoroni import Button  # Import Buttons
from picographics import PicoGraphics  # Import universal graphics library (part of custom UF2 file)
from picographics import DISPLAY_PICO_DISPLAY  # Class for this display model
from picographics import PEN_P4  # Class for the color depth used
import time
from math import ceil
from collections import OrderedDict
import os

display = PicoGraphics(display=DISPLAY_PICO_DISPLAY,
                       pen_type=PEN_P4,
                       rotate=0)  # Create display object

X_MAX, Y_MAX = display.get_bounds()

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


if __name__ == "__main__":
    try:
        f = open("settings.txt", "r")
        # continue with the file.
    except OSError:  # open failed (file not found)
        import setup

        setup.initial()

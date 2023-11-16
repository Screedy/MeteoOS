from pimoroni import Button  # Import Buttons
from picographics import PicoGraphics  # Import universal graphics library (part of custom UF2 file)
from picographics import DISPLAY_PICO_DISPLAY  # Class for this display model
from picographics import PEN_P4  # Class for the color depth used


display = PicoGraphics(display=DISPLAY_PICO_DISPLAY,
                       pen_type=PEN_P4,
                       rotate=0)  # Create display object

X_MAX, Y_MAX = display.get_bounds()  # 240 x 135

button_a = Button(12)
button_b = Button(13)
button_x = Button(14)
button_y = Button(15)


class Colors:
    BLACK = display.create_pen(0, 0, 0)  # Create color black
    WHITE = display.create_pen(255, 255, 255)  # Create color white
    RED = display.create_pen(255, 0, 0)  # Create color red
    GREEN = display.create_pen(0, 255, 0)  # Create color green

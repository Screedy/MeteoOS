import main

# display = main.display


def text_ok(x: int, y: int, display, color: int = main.WHITE):
    """Draws an OK text on the display at the given coordinates.
    Uses the global display object.

    :param x: The x coordinate of the button.
    :param y: The y coordinate of the button.
    :param display: The display object where the text will be drawn.
    :param color: The color of the button. Uses the pico_graphics create_pen() function to create a color.
    :return: None
    """

    display.set_pen(color)
    display.text("OK", x, y, 20, 1)


def text_help(x: int, y: int, display, color: int = main.WHITE):
    """Draws a help text on the display at the given coordinates.
    Uses the global display object.

    :param x: The x coordinate of the button.
    :param y: The y coordinate of the button.
    :param display: The display object where the text will be drawn.
    :param color: The color of the button. Uses the pico_graphics create_pen() function to create a color.
    :return: None
    """

    display.set_pen(color)
    display.text("HELP", x, y, 40, 1)

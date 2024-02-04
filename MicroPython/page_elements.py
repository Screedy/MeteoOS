import time

from config import Colors, GraphInterval, Display
from graphics import draw_arrow, draw_clock, draw_thermometer, draw_humidity
import temp_sensor
from settings import SettingItems


def clear_fast():
    """Clears the display without refreshing the display to remove flickering."""

    display = Display()

    display().set_pen(Colors.BLACK)  # Set pen color to black
    display().clear()  # Clear display


def render_nav_arrows(x: int, color: int = Colors.WHITE):
    """Draws navigation arrows on the screen with the given coordinates.
    Keeps the arrows height consistent across screens.

    :param x: The x coordinate of the arrows.
    :param color: The color of the arrows. Uses the pico_graphics create_pen() function to create a color.
        (Default: Colors.WHITE)
    :return: None
    """

    display = Display()

    display().set_pen(color)
    # draw_arrow(x, 20, 10, 180, display)
    # draw_arrow(x, 100, 10, 0, display)

    draw_arrow(x, 7, 16, 180)
    draw_arrow(x-1, 113, 17, 0)


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


def render_sensor_details(x: int, sensor_id: int):
    """Draws the sensor details on the screen with the given coordinates.

    :param x: The x coordinate of the sensor details.
    :param sensor_id: The sensor id of the sensor to draw the details of.
    :return: None
    """

    display = Display()

    test_sensor = temp_sensor.DHT11(0, "TOILET")  # TODO: change to real sensor

    display().text(test_sensor.name, 34, 7, 250, 2)
    draw_clock(14, 41)
    current_time = time.localtime()
    display().text(parse_time(current_time), 34, 34, 250, 2)
    draw_thermometer(14, 68)

    display().text(f"{test_sensor.temperature}°C", 34, 61, 250, 2)
    draw_humidity(14, 96)
    display().text(f"{test_sensor.humidity}%", 34, 88, 250, 2)     # TODO: draw humidity next to the humidity icon


def render_homepage_buttons(interval: GraphInterval = GraphInterval.Daily):
    """Draws the homepage buttons on the screen.

    :param interval: The interval to display on the button. (Default: "D") Can be "D" (Daily), "W" (Weekly) or
        "M" (Monthly).
    :return: None
    """

    display = Display()

    active_color = Colors.WHITE
    inactive_color = Colors.BLACK

    display().set_pen(active_color) if interval == GraphInterval.Daily else display().set_pen(inactive_color)
    display().rectangle(189, 8, 13, 13)
    display().set_pen(inactive_color) if interval == GraphInterval.Daily else display().set_pen(active_color)
    display().text("D", 190, 7, 250, 2)

    display().set_pen(active_color) if interval == GraphInterval.Weekly else display().set_pen(inactive_color)
    display().rectangle(204, 8, 13, 13)
    display().set_pen(inactive_color) if interval == GraphInterval.Weekly else display().set_pen(active_color)
    display().text("W", 205, 7, 250, 2)

    display().set_pen(active_color) if interval == GraphInterval.Monthly else display().set_pen(inactive_color)
    display().rectangle(219, 8, 13, 13)
    display().set_pen(inactive_color) if interval == GraphInterval.Monthly else display().set_pen(active_color)
    display().text("M", 220, 7, 250, 2)

    display().text("MENU", 190, 115, 250, 2)


def render_settings_buttons():
    """Draws the settings buttons on the screen.

    :return: None
    """

    display = Display()

    display().text("Settings", 135, 7, 250, 2)
    display().text("BACK", 190, 115, 250, 2)


def render_settings_items(selected_item: int = 0):
    """Draws the settings items on the screen.

    :param selected_item: The selected item to highlight. (Default: 0)
    :return: None
    """

    display = Display()
    number_of_items = len(SettingItems.list_of_items())
    page_start_item = selected_item - (selected_item % 3)

    for i in range(3):
        if page_start_item + i >= number_of_items:
            break

        display().set_pen(Colors.WHITE) if i == selected_item % 3 else display().set_pen(Colors.BLACK)
        display().rectangle(120, 34 + (i * 27), 110, 15)
        display().set_pen(Colors.BLACK) if i == selected_item % 3 else display().set_pen(Colors.WHITE)
        display().text(SettingItems.list_of_items()[page_start_item + i], 123, 34 + (i * 27), 250, 2)

        if i == selected_item % 3:
            display().set_pen(Colors.WHITE)
            display().text(">", 110, 34 + (i * 27), 250, 2)
        else:
            display().set_pen(Colors.BLACK)
            display().rectangle(110, 34 + (i * 27), 10, 15)

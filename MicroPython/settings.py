import time
from config import *
import page_elements


class Settings:
    """Class for all options in the settings menu page."""

    def __init__(self):
        """Initializes the settings menu."""

        pass

    def add_sensor(self):
        """Adds a sensor to the list of sensors."""

        pass

    def remove_sensor(self):
        """Removes a sensor from the list of sensors."""

        pass


def render_settings():
    """Renders the settings page."""

    display = Display()

    page_elements.clear_fast()
    display().set_pen(Colors.WHITE)
    page_elements.render_sensor_details(30, 1)
    page_elements.render_nav_arrows(110)

    display().line(101, 16, 101, 120, 3)

    page_elements.render_settings_buttons()
    page_elements.render_settings_items()

    display().update()

    # print("Settings rendered")


def settings_loop():
    """The settings loop that runs when settings page is active."""

    while True:
        if button_x.read():
            pass

        if button_y.read():
            return

        if button_a.read():
            pass

        if button_b.read():
            pass

        render_settings()
        time.sleep(0.1)

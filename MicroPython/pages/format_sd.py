import time
from config.config import *
import page_elements
import sdcard
from config.sdcard_manager import SDCardManager


def render_format_sd():
    """Renders the page for formatting the SD card."""

    display = Display()

    page_elements.clear_fast()
    display().set_pen(Colors.WHITE)
    display().text("Format SD card", 2, 0, 236, 2)
    display().set_pen(Colors.RED)
    display().text("Are you sure you want to format the SD card?", 2, 20, 236, 2)
    display().text("Press Y to confirm", 2, display.y_max - 20, 236, 2)
    display().update()

    while not button_y.read():
        if button_x.read():
            return False
        time.sleep(0.1)

    format_sd()

    return True


def format_sd():
    """Formats the SD card."""

    sd = SDCardManager()

    if sd.is_mounted():
        sd.format()

        return True

    return False
import time
from config.config import *
import page_elements


class SettingItems:
    """An enum class for the different settings items.

    :param AddSensor: Add sensor to a list of sensors.
    :param RemSensor: Remove a sensor from list.
    :param Brightness: Change brightness of the display.
    :param FormatSD: Format the SD card.
    """

    AddSensor = 0
    RemSensor = 1
    Brightness = 2
    FormatSD = 3

    @staticmethod
    def list_of_items():
        """Returns a list of items in the enum.

        :return: Returns a list of items in the enum.
        """

        return [item for item in dir(SettingItems) if
                not item.startswith("__") and not callable(getattr(SettingItems,
                                                                   item))]

    @staticmethod
    def get_function(selected_item: int):
        """Gets the function of the selected item.

        :param selected_item: The selected item.
        :return: The function of the selected item.
        """

        if selected_item == SettingItems.AddSensor:
            return Settings.add_sensor()
        elif selected_item == SettingItems.RemSensor:
            return Settings.remove_sensor()
        elif selected_item == SettingItems.Brightness:
            return Settings.change_brightness()
        elif selected_item == SettingItems.FormatSD:
            return Settings.format_sd()


class Settings:
    """Class for all options in the settings menu page."""

    def __init__(self):
        """Initializes the settings menu."""

        pass

    @classmethod
    def add_sensor(cls):
        """Adds a sensor to the list of sensors."""

        print("Adding sensor...")
        pass

    @classmethod
    def remove_sensor(cls):
        """Removes a sensor from the list of sensors."""

        pass

    @classmethod
    def change_brightness(cls):
        """Changes the brightness of the display."""

        pass

    @classmethod
    def format_sd(cls):
        """Formats the SD card."""

        pass


def render_settings(selected_item: int = 0):
    """Renders the settings page."""

    display = Display()

    page_elements.clear_fast()
    display().set_pen(Colors.WHITE)
    # page_elements.render_sensor_details(30, 1)
    page_elements.render_nav_arrows(110)

    display().line(101, 16, 101, 120, 3)

    page_elements.render_settings_buttons()
    page_elements.render_settings_items(selected_item)

    display().update()

    # print("Settings rendered")


def settings_loop():
    """The settings loop that runs when settings page is active."""

    selected_item = 0
    settings_list = SettingItems.list_of_items()

    while True:
        if button_x.read():
            print(f"Item {selected_item} selected")
            SettingItems.get_function(selected_item)

        if button_y.read():
            return

        if button_a.read():
            selected_item = (selected_item - 1) % len(settings_list)
            # print(f"{selected_item}")

        if button_b.read():
            selected_item = (selected_item + 1) % len(settings_list)
            # print(f"{selected_item}")

        render_settings(selected_item)
        time.sleep(0.1)

from config.brightness import load_brightness
from config.config import singleton


@singleton
class SettingsManager:
    """Singleton class for managing the settings variables. This class is used for loading and saving settings to
    a file as well as managing the settings in the program during runtime."""

    # TODO: Add more settings when needed.

    _brightness = None

    def __init__(self):
        """Create the settings object."""

        self._brightness = load_brightness()

    @property
    def brightness(self):
        """The brightness of the display.

        :return: The brightness of the display.
        """

        return self._brightness

    @brightness.setter
    def brightness(self, brightness: int):
        """Sets the brightness of the display.

        :param brightness: The brightness of the display.
        """

        self._brightness = brightness
        self.save_brightness()

    def save_brightness(self):
        """Used to save the brightness to a file."""

        with open("settings.txt", "r") as fr_settings:
            lines = fr_settings.readlines()

            for i in range(len(lines)):
                if "brightness:" in lines[i]:
                    lines[i] = f"brightness:{self._brightness}\n"
                    break

        with open("settings.txt", "w") as fw_settings:
            fw_settings.writelines(lines)

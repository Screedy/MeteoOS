from config.config import singleton, Display


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

        if brightness < 1 or brightness > 10:
            raise ValueError("Brightness must be between 1 and 10")

        self._brightness = brightness
        self.save_brightness()

        display = Display()
        display().set_backlight(brightness / 10)

    def save_brightness(self):
        """Used to save the brightness to a file."""

        lines = None
        has_brightness = False

        with open("settings.txt", "r") as fr_settings:
            lines = fr_settings.readlines()

            for i in range(len(lines)):
                if "brightness:" in lines[i]:
                    lines[i] = f"brightness:{self._brightness}\n"
                    has_brightness = True
                    break

        with open("settings.txt", "w") as fw_settings:
            for line in lines:
                fw_settings.write(line)

            if not has_brightness:
                print("No brightness found, adding new line")
                fw_settings.write(f"brightness:{self._brightness}\n")


def load_brightness():
    """Loads the brightness from the config file."""

    with open("settings.txt", "r") as fr:
        for line in fr:
            if line.startswith("brightness"):
                return float(line.split(":")[1])

    return 0.5


if __name__ == "__main__":
    settings = SettingsManager()
    print(settings.brightness)

    settings.brightness = 9

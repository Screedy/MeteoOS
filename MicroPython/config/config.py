from pimoroni import Button  # Import Buttons
from picographics import PicoGraphics  # Import universal graphics library (part of custom UF2 file)
from picographics import DISPLAY_PICO_DISPLAY  # Class for this display model
from picographics import PEN_P4  # Class for the color depth used


button_a = Button(12)
button_b = Button(13)
button_x = Button(14)
button_y = Button(15)


def singleton(class_):
    """A decorator for making a class a singleton.

    :param class_: The class to make a singleton.
    :return: The singleton class.
    """

    instances = {}

    def get_instance(*args, **kwargs):
        """Return the instance of the class if it exists, else create a new instance."""

        if class_ not in instances:
            instances[class_] = class_(*args, **kwargs)

        return instances[class_]

    return get_instance


@singleton
class Display:
    """Singleton class for managing the only display object."""
    def __init__(self):
        """Create the display object."""

        self._display = PicoGraphics(display=DISPLAY_PICO_DISPLAY,
                                     pen_type=PEN_P4,
                                     rotate=0)

        self._x_max, self._y_max = self._display.get_bounds()

    def __call__(self):
        return self._display

    @property
    def x_max(self):
        return self._x_max

    @property
    def y_max(self):
        return self._y_max


class Colors:
    """Class for colors used in the program.

    :param BLACK: The color black.
    :param WHITE: The color white.
    :param RED: The color red.
    :param GREEN: The color green.
    """

    display = Display()

    BLACK = display().create_pen(0, 0, 0)  # Create color black
    WHITE = display().create_pen(255, 255, 255)  # Create color white
    RED = display().create_pen(255, 0, 0)  # Create color red
    GREEN = display().create_pen(0, 255, 0)  # Create color green
    GREY = display().create_pen(128, 128, 128)  # Create color grey


class Page:
    """An enum class for the different pages.

    :param Homepage: The homepage.
    :param Settings: The settings page.
    """

    Homepage = 0
    Settings = 1


class GraphInterval:
    """An enum class for the different graph intervals.

    :param Daily: The daily graph interval.
    :param Weekly: The weekly graph interval.
    :param Monthly: The monthly graph interval.
    """

    Daily = 0
    Weekly = 1
    Monthly = 2


if __name__ == "__main__":
    display_test = Display()
    display_test2 = Display()

    print(id(display_test))
    print(id(display_test2))

    display_test().set_pen(Colors.WHITE)

    # display_test().line(0, 0, 100, 100)
    display_test2().line(100, 100, 200, 200)
    display_test().update()

    print(display_test.x_max)


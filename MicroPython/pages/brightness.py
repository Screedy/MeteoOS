import time
from config.config import *
from sensors.sensor_manager import SensorManager, AvailableSensors
import page_elements


def render_brightness():
    """Renders the page for changing the brightness of the display."""

    display = Display()
    brightness = load_brightness()

    page_elements.clear_fast()
    display().set_pen(Colors.WHITE)
    display().text("Change brightness", 2, 0, 236, 2)
    display().text("Press A to increase brightness", 2, 20, 236, 2)
    display().text("Press B to decrease brightness", 2, 40, 236, 2)
    display().text("Press Y to confirm", 2, display.y_max - 20, 236, 2)

    render_nice_slider(brightness)

    display().update()

    while not button_y.read():
        if button_a.read():
            brightness = (brightness + 0.1) if brightness < 1 else 1
        elif button_b.read():
            brightness = (brightness - 0.1) if brightness > 0 else 0
        display().set_brightness(brightness)


def load_brightness():
    """Loads the brightness from the config file."""

    with open("settings.txt", "r") as fr:
        for line in fr:
            if line.startswith("brightness"):
                return line.split(":")[1]

    return 0.5


def render_nice_slider(brightness):
    """Renders a slider indicating the brightness."""

    display = Display()

    display().set_pen(Colors.GREY)
    display().rectangle(38, 58, 160, 14)

    display().set_pen(Colors.WHITE)
    display().text("0.1", 10, 58, 236, 2)
    display().text("1.0", 205, 58, 236, 2)
    for i in range(0, brightness*10):
        display().line(50+i*15, 60, 50+i*15, 70, 10)


if __name__ == "__main__":
    render_nice_slider(0.5)

    display = Display()

    display().update()


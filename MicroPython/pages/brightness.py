import time
from config.config import *
from sensors.sensor_manager import SensorManager, AvailableSensors
import page_elements


def render_brightness():
    """Renders the page for changing the brightness of the display."""

    display = Display()
    brightness = load_brightness() * 10

    page_elements.clear_fast()
    display().set_pen(Colors.WHITE)
    display().text("Change brightness", 2, 0, 236, 2)

    render_nice_slider(brightness)

    display().update()

    while not button_y.read():
        page_elements.clear_fast()
        display().set_pen(Colors.WHITE)
        display().text("Change brightness", 2, 0, 236, 2)
        render_nice_slider(brightness)

        if button_a.read():
            if brightness < 10:
                brightness = brightness + 1
            print(brightness)
        elif button_b.read():
            if brightness > 0:
                brightness = brightness - 1
            print(brightness)
        display().set_backlight(brightness/10)
        display().update()


def load_brightness():
    """Loads the brightness from the config file."""

    with open("settings.txt", "r") as fr:
        for line in fr:
            if line.startswith("brightness"):
                return float(line.split(":")[1])

    return 0.5


def render_nice_slider(brightness):
    """Renders a slider indicating the brightness."""

    display = Display()

    display().set_pen(Colors.GREY)
    display().rectangle(38, 58, 160, 14)

    display().set_pen(Colors.WHITE)
    display().text("0.1", 10, 58, 236, 2)
    display().text("1.0", 205, 58, 236, 2)
    for i in range(0, brightness):
        display().line(50+i*15, 60, 50+i*15, 70, 10)


if __name__ == "__main__":
    render_brightness()

from config.config import Display, Colors, button_x, button_a, button_b, button_y
from graphics import page_elements
from config.settings_manager import SettingsManager, load_brightness
from graphics.graphics import draw_cancel, draw_confirm


def render_brightness():
    """Renders the page for changing the brightness of the display.


    rationale brightness: The brightness is a number between 0 and 1. Using floats in MicroPython resulted in the
        value being not implemented correctly. Therefore, the brightness is multiplied by 10 to be an integer and
        divided by 10 when setting the backlight of the display.
    """

    display = Display()
    brightness = load_brightness()
    old_brightness = brightness

    page_elements.clear_fast()
    display().set_pen(Colors.WHITE)
    display().text("Change brightness", 2, 0, 236, 2)

    render_nice_slider(brightness)

    display().update()

    while not button_x.read():
        page_elements.clear_fast()
        display().set_pen(Colors.WHITE)
        display().text("Change brightness", 2, 0, 236, 2)
        render_nice_slider(brightness)

        if button_a.read():
            if brightness < 10:
                brightness = brightness + 1
            print(brightness)
        elif button_b.read():
            if brightness > 1:
                brightness = brightness - 1
            print(brightness)
        elif button_y.read():
            display().set_backlight(old_brightness / 10)
            return False

        display().set_backlight(brightness / 10)
        display().update()

    settings = SettingsManager()
    settings.brightness = brightness

    return True


def render_nice_slider(brightness):
    """Renders a slider indicating the brightness."""

    display = Display()

    display().set_pen(Colors.GREY)
    display().rectangle(38, 58, 160, 14)

    draw_confirm()
    draw_cancel()

    display().set_pen(Colors.WHITE)
    display().text("0.1", 10, 58, 236, 2)
    display().text("1.0", 205, 58, 236, 2)
    for i in range(0, brightness):
        display().line(50+i*15, 60, 50+i*15, 70, 10)


if __name__ == "__main__":
    render_brightness()

from config.config import Colors, Display
from config.buttons import button_a, button_b, button_x, button_y
import graphics.graphics_text as graphics_text
from utime import sleep


def help_interrupt():
    """Interrupts the current function and displays the help screen."""
    import qr_code

    display = Display()

    qr_code.render_help()

    graphics_text.text_ok(display.x_max - 25, display.y_max - 17, display, Colors.BLACK)
    display().update()

    while not button_y.read():
        sleep(.15)

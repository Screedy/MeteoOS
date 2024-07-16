import qrcode

from config.config import Colors, Display
from utils.decorators import execution_time
from config.env import env_vars
from graphics.graphics import draw_back


def measure_qr_code(size, code):
    """
    Calculates the size of the QR code and the size of each module.

    :param size: The maximum size of the QR code.
    :param code: The QR code object.
    :return: The size of the QR code and the size of each module.
    """

    w, h = code.get_size()
    module_size = int(size / w)
    return module_size * w, module_size


if env_vars['TEST_MEASUREMENT']:
    @execution_time
    def draw_qr_code(ox, oy, size, code):
        draw_qr_code_body(ox, oy, size, code)
else:
    def draw_qr_code(ox, oy, size, code):
        draw_qr_code_body(ox, oy, size, code)


def draw_qr_code_body(ox, oy, size, code):
    """
    Draws the QR code on the display.

    :param ox: The x offset.
    :param oy: The y offset.
    :param size: The size of the QR code.
    :param code: The QR code object.
    :return: None
    """

    display = Display()

    size, module_size = measure_qr_code(size, code)

    display().set_pen(Colors.BLACK)
    display().rectangle(ox, oy, size, size)
    display().set_pen(Colors.WHITE)
    for x in range(size):
        for y in range(size):
            if code.get_module(x, y):
                display().rectangle(ox + x * module_size, oy + y * module_size, module_size, module_size)


if env_vars['TEST_MEASUREMENT']:
    @execution_time
    def render_help(url: str = "https://github.com/Screedy/MeteoOS"):
        render_help_body(url)
else:
    def render_help(url: str = "https://github.com/Screedy/MeteoOS"):
        render_help_body(url)


def render_help_body(url):
    """
    Renders QR code with the given URL address and displays it on the screen.

    :param url: The URL address to be encoded.
    :return: None
    """

    display = Display()

    code = qrcode.QRCode()
    code.set_text(url)

    display().set_pen(Colors.BLACK)
    display().clear()
    display().set_pen(Colors.WHITE)

    max_size = min(display.x_max, display.y_max)

    size, module_size = measure_qr_code(max_size, code)
    # left = int((display.x_max // 2) - (size // 2))
    # top = int((display.y_max // 2) - (size // 2))
    left = 10
    top = 10
    draw_qr_code(left, top, max_size, code)
    display().text("Scan for help", 135, 10, display.x_max - 135, 2)
    draw_back()

    display().update()


if __name__ == "__main__":
    render_help()

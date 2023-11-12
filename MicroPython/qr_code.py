import qrcode

import main
import time


display = main.display
WIDTH, HEIGHT = display.get_bounds()


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


def draw_qr_code(ox, oy, size, code):
    """
    Draws the QR code on the display.

    :param ox: The x offset.
    :param oy: The y offset.
    :param size: The size of the QR code.
    :param code: The QR code object.
    :return: None
    """

    size, module_size = measure_qr_code(size, code)

    display.set_pen(main.WHITE)
    display.rectangle(ox, oy, size, size)
    display.set_pen(main.BLACK)
    for x in range(size):
        for y in range(size):
            if code.get_module(x, y):
                display.rectangle(ox + x * module_size, oy + y * module_size, module_size, module_size)


def render_help(url: str = "https://github.com/Screedy/MeteoOS"):
    """
    Renders QR code with the given URL address and displays it on the screen.

    :param url: The URL address to be encoded.
    :return: None
    """

    code = qrcode.QRCode()
    code.set_text(url)

    display.set_pen(main.WHITE)
    display.clear()
    display.set_pen(main.BLACK)

    max_size = min(WIDTH, HEIGHT)

    size, module_size = measure_qr_code(max_size, code)
    left = int((WIDTH // 2) - (size // 2))
    top = int((HEIGHT // 2) - (size // 2))
    draw_qr_code(left, top, max_size, code)

    display.update()
import qrcode

from config.config import Colors, Display


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

    display = Display()

    size, module_size = measure_qr_code(size, code)

    display().set_pen(Colors.WHITE)
    display().rectangle(ox, oy, size, size)
    display().set_pen(Colors.BLACK)
    for x in range(size):
        for y in range(size):
            if code.get_module(x, y):
                display().rectangle(ox + x * module_size, oy + y * module_size, module_size, module_size)


def render_help(url: str = "https://github.com/Screedy/MeteoOS"):
    """
    Renders QR code with the given URL address and displays it on the screen.

    :param url: The URL address to be encoded.
    :return: None
    """

    display = Display()

    code = qrcode.QRCode()
    code.set_text(url)

    display().set_pen(Colors.WHITE)
    display().clear()
    display().set_pen(Colors.BLACK)

    max_size = min(display.x_max, display.y_max)

    size, module_size = measure_qr_code(max_size, code)
    left = int((display.x_max // 2) - (size // 2))
    top = int((display.y_max // 2) - (size // 2))
    draw_qr_code(left, top, max_size, code)

    display().update()

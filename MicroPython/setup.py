from pimoroni import Button  # Import Buttons
from picographics import PicoGraphics  # Import universal graphics library (part of custom UF2 file)
from picographics import DISPLAY_PICO_DISPLAY  # Class for this display model
from picographics import PEN_P4  # Class for the color depth used

import main
from main import display, clear_fast
import time

helped = False
pins = ["GP0", "GP1", "GP2", "GP3", "GP4", "GP5", "GP6", "GP7", "GP8", "GP9", "GP14", "GP15", "GP16", "GP17", "GP18",
        "GP19"]
selected_pin = 0
storage_pin = 0


def wizard_start():
    """Starts the setup wizard"""

    clear_fast()
    display.set_pen(main.WHITE)
    display.text("Setup wizard", 2, 0, 240, 2)
    display.text("Welcome to your new thermal buddy!\nLet's get everything setup.", 2, 20, 240, 2)
    display.text("Press Y to continue", 2, main.Y_MAX - 20, 240, 2)
    display.update()

    wait_for_y(wizard_start)


def pin_setup():
    """Sets up the pins for first thermal sensor"""

    global selected_pin

    def render_screen():
        """Renders the pin setup screen"""

        clear_fast()
        display.set_pen(main.WHITE)
        display.text("Setup wizard", 2, 0, 236, 2)
        display.text("Please select the correct pin for your first thermal sensor with A and B buttons", 2, 20, 236, 2)
        display.text("OK", main.X_MAX - 30, main.Y_MAX - 20, 240, 2)

    render_screen()

    while not main.button_y.read():
        if main.button_x.read():
            help_interrupt()
            render_screen()

        if main.button_a.read():
            selected_pin = (selected_pin + 1) % len(pins)

        if main.button_b.read():
            selected_pin = (selected_pin - 1) % len(pins)

        clear_pin()
        display.text(f"PIN: {pins[selected_pin]}", 2, main.Y_MAX - 40, 200, 2)
        display.update()
        time.sleep(.15)


def storage_pin_setup():
    """"""

    global storage_pin

    def render_screen():
        clear_fast()
        display.set_pen(main.WHITE)
        display.text("Setup wizard", 2, 0, 236, 2)
        display.text("Please connect the SD card adapter to the following pins:", 2, 20, 236, 2)
        display.text("SCK -> GP2, MOSI -> GP3, "
                     "MISO -> GP4, CS -> GP5, VCC -> +5V, GND -> GND", 2, 70, 236, 2)
        display.text("OK", main.X_MAX - 30, main.Y_MAX - 20, 240, 2)
        display.update()

    render_screen()

    wait_for_y(storage_pin_setup)

    from device_test import test_storage
    if not test_storage():
        clear_fast()
        display.text("SD card not detected, please check the connections and try again.", 2, 100, 236, 2)
        display.update()
        time.sleep(5)
        storage_pin_setup()


def help_interrupt():
    import qr_code

    qr_code.render_help()


def initial():
    f = open("settings.txt", "w")

    wizard_start()
    pin_setup()
    storage_pin_setup()


def wait_for_y(parent_function):
    while True:
        if main.button_y.read():
            return
        if main.button_x.read():
            help_interrupt()
            return parent_function()


def clear_pin():
    main.display.set_pen(main.BLACK)
    main.display.rectangle(0, main.Y_MAX - 40, 120, main.Y_MAX - 20)
    main.display.set_pen(main.WHITE)


if __name__ == "__main__":
    print("Initial testing of setup file")
    initial()

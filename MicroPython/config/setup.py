from config.config import Colors, Display
from config.buttons import button_a, button_b, button_x, button_y
import graphics.graphics_text as graphics_text
from utime import sleep
from graphics.page_elements import clear_fast
from pages.add_sensor import render_add_sensor
from utils.misc_utils import help_interrupt

helped = False
pins = ["GP0", "GP1", "GP9", "GP10", "GP11", "GP20", "GP21", "GP22"]
selected_pin = 0
storage_pins = ["GP10", "GP11", "GP8", "GP9"]


def wizard_start():
    """Starts the wizard for first time setup."""

    set_defaults()

    display = Display()

    clear_fast()
    display().set_pen(Colors.WHITE)
    display().text("Setup wizard", 2, 0, 240, 2)
    display().text("Welcome to your new thermal buddy!\nLet's get everything setup.", 2, 20, 240, 2)
    display().text("Press Y to continue", 2, display.y_max - 20, 240, 2)
    display().update()

    wait_for_y(wizard_start)


def storage_pin_setup():
    """Sets up the pins for the SD card adapter."""

    display = Display()

    def render_screen():
        clear_fast()
        display().set_pen(Colors.WHITE)
        display().text("Setup wizard", 2, 0, 236, 2)
        display().text("Please connect the SD card to the following pins:", 2, 20, 180, 2)
        display().text("SCK -> GP10, MOSI -> GP11, "
                       "MISO -> GP8, CS -> GP9, VCC -> +5V, GND -> GND", 2, 70, 220, 2)
        display().text("OK", display.x_max - 25, display.y_max - 17, 236, 2)
        display().text("HELP", display.x_max - 45, 2, 236, 2)
        display().update()

    render_screen()

    wait_for_y(storage_pin_setup)

    from utils.device_tests import test_storage
    if not test_storage():
        clear_fast()
        display().text("SD card not detected, please check the connections and try again.", 2, 100, 236, 2)
        display().update()
        sleep(5)
        storage_pin_setup()


def initial():
    """Initiates the first time setup. This function is called when the settings.txt file is not found.
    Guides the user through the setup process and connects first thermal sensor and SD card.
    """
    f = open("settings.txt", "w")

    wizard_start()
    storage_pin_setup()
    render_add_sensor(True)

    f.write(f"PIN: {pins[selected_pin]}\n")
    f.write(f"STORAGE: {storage_pins[0]} {storage_pins[1]} {storage_pins[2]} {storage_pins[3]}\n")


def wait_for_y(parent_function: callable):
    """Waits for the Y button to be pressed and then returns to the parent function.
    If the X button is pressed, the help screen is displayed with QR code to the GitHub repository."""

    while True:
        if button_y.read():
            return
        if button_x.read():
            help_interrupt()
            return parent_function()


def clear_pin():
    """Clears the pin number on the screen."""

    display = Display()

    display().set_pen(Colors.BLACK)
    display().rectangle(0, display.y_max - 40, 120, display.y_max - 20)
    display().set_pen(Colors.WHITE)


def set_defaults():
    """Sets the default values for the settings.txt file."""

    with open("settings.txt", "w") as f:
        f.write("brightness:0.5\n")


if __name__ == "__main__":
    print("Initial testing of setup file")
    initial()
    print("Setup file tested successfully")

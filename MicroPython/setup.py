from config.config import Colors, Display
from config.config import button_a, button_b, button_x, button_y
import graphics.graphics_text as graphics_text
import time
from page_elements import clear_fast

helped = False
pins = ["GP4", "GP5", "GP9", "GP10", "GP11", "GP20", "GP21", "GP22"]
selected_pin = 0
storage_pins = ["GP0", "GP1", "GP2", "GP3"]


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


def pin_setup():
    """Sets up the pins for first thermal sensor."""

    global selected_pin

    display = Display()

    def render_screen():
        """Renders the pin setup screen."""

        clear_fast()
        display().set_pen(Colors.WHITE)
        display().text("Setup wizard", 2, 0, 236, 2)
        display().text("Please select the correct pin for your first thermal sensor with A and B buttons",
                       2, 20, 236, 2)
        display().text("OK", display.x_max - 25, display.y_max - 17, 236, 2)
        display().text("HELP", display.x_max - 45, 2, 236, 2)

    render_screen()

    while not button_y.read():
        if button_x.read():
            help_interrupt()
            render_screen()

        if button_a.read():
            selected_pin = (selected_pin + 1) % len(pins)

        if button_b.read():
            selected_pin = (selected_pin - 1) % len(pins)

        clear_pin()
        display().text(f"PIN: {pins[selected_pin]}", 2, display.y_max - 40, 200, 2)
        display().update()
        time.sleep(.15)


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

    from device_tests import test_storage
    if not test_storage():
        clear_fast()
        display().text("SD card not detected, please check the connections and try again.", 2, 100, 236, 2)
        display().update()
        time.sleep(5)
        storage_pin_setup()


def help_interrupt():
    """Interrupts the current function and displays the help screen."""
    import qr_code

    display = Display()

    qr_code.render_help()

    graphics_text.text_ok(display.x_max - 25, display.y_max - 17, display, Colors.BLACK)
    display().update()

    while not button_y.read():
        time.sleep(.15)


def initial():
    """Initiates the first time setup. This function is called when the settings.txt file is not found.
    Guides the user through the setup process and connects first thermal sensor and SD card.
    """
    f = open("settings.txt", "w")

    wizard_start()
    pin_setup()
    storage_pin_setup()

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
    """Sets the default values for the settings.txt file."""    # TODO: Add more settings

    with open("settings.txt", "w") as f:
        f.write("brightness:0.5\n")


if __name__ == "__main__":
    print("Initial testing of setup file")
    initial()
    print("Setup file tested successfully")

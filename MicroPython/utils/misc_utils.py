from config.config import Colors, Display
from config.buttons import button_a, button_b, button_x, button_y
import graphics.graphics_text as graphics_text
from utime import sleep
import sys
import uselect
from config.env import env_vars


input_buffer = ""


def help_interrupt():
    """Interrupts the current function and displays the help screen."""
    import qr_code

    display = Display()

    qr_code.render_help()

    graphics_text.text_ok(display.x_max - 25, display.y_max - 17, display, Colors.BLACK)
    display().update()

    while not button_y.read():
        sleep(.15)


def handle_input(spoll):
    """Handle user input one character at a time without blocking"""
    global input_buffer
    if spoll.poll(0):
        char = sys.stdin.read(1)
        if char:
            if char == '\n':
                cmd = input_buffer.strip()
                input_buffer = ""
                return cmd
            else:
                input_buffer += char
    return None


def handle_interrupt():
    poll = uselect.poll()
    poll.register(sys.stdin, uselect.POLLIN)

    while True:
        try:
            cmd = handle_input(poll)
            if cmd:
                if env_vars['DEBUG']:
                    print(f"Executing command: {cmd}")
                try:
                    exec(cmd)
                except Exception as e:
                    print(f"Error executing command: {e}")
            sleep(0.1)
        except Exception as e:
            print("Error in main loop:", e)

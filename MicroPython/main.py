import time
import _thread

from config import *
# import graphics_text
import graphics
import page_elements


def clear_fast():
    """Clears the display without refreshing the display to remove flickering."""

    display.set_pen(Colors.BLACK)  # Set pen color to black
    display.clear()  # Clear display


def render_homepage(sensor_number, graph_interval):
    """Renders the homepage with information about the selected sensor and selected graph interval.

    :param sensor_number: The selected sensor number.
    :param graph_interval: The selected graph interval. Either 1 (Hourly), 2 (Daily), 3 (Weekly) or 4 (Monthly).
    :return: None
    """

    clear_fast()
    display.set_pen(Colors.WHITE)
    page_elements.render_nav_arrows(8, display)
    page_elements.render_sensor_details(30, display, 1)

    display.line(100, 10, 100, 120, 2)

    display.update()

    print("Homepage rendered")


def main_task():
    """The main task that runs in the background."""

    while True:
        time.sleep(.15)

        if button_x.read():
            # TODO: change the graph interval
            pass
        if button_y.read():
            # TODO: go to settings
            pass
        if button_a.read():
            # TODO: change the sensor to previous one
            pass
        if button_b.read():
            # TODO: change the sensor to next one
            pass

        print("Main task running")
        time.sleep(5)


if __name__ == "__main__":
    try:
        f = open("settings.txt", "r")
        # continue with the file.
    except OSError:  # open failed (file not found)
        import setup

        setup.initial()

    try:
        fr_homepage = open("homepage_settings.txt", "r")
    except OSError:
        fw_homepage = open("homepage_settings.txt", "w")
        fw_homepage.write("0\n0")
        fw_homepage.close()
        fr_homepage = open("homepage_settings.txt", "r")

    last_sensor = int(fr_homepage.readline())
    last_graph_interval = int(fr_homepage.readline())
    fr_homepage.close()

    render_homepage(last_sensor, last_graph_interval)

    _thread.start_new_thread(main_task, ())

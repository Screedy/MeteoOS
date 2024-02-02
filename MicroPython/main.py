import time
import _thread

from config import *
# import graphics_text
import graphics
import page_elements
import temp_sensor
# from homepage import homepage_loop


def clear_fast():
    """Clears the display without refreshing the display to remove flickering."""

    display = Display()

    display().set_pen(Colors.BLACK)  # Set pen color to black
    display().clear()  # Clear display


def render_homepage(sensor_number, graph_interval):
    """Renders the homepage with information about the selected sensor and selected graph interval.

    :param sensor_number: The selected sensor number.
    :param graph_interval: The selected graph interval. Either 1 (Hourly), 2 (Daily), 3 (Weekly) or 4 (Monthly).
    :return: None
    """

    display = Display()

    clear_fast()
    display().set_pen(Colors.WHITE)
    page_elements.render_nav_arrows(6)
    page_elements.render_sensor_details(30, 1)

    display().line(101, 16, 101, 120, 3)

    page_elements.render_homepage_buttons(graph_interval)

    display().update()

    # print("Homepage rendered")


def render_settings():
    """Renders the settings page."""

    display = Display()

    clear_fast()
    display().set_pen(Colors.WHITE)
    page_elements.render_sensor_details(30, 1)
    page_elements.render_nav_arrows(110)

    display().line(101, 16, 101, 120, 3)

    page_elements.render_settings_buttons()
    page_elements.render_settings_items()

    display().update()

    # print("Settings rendered")


def main_task():
    """The main task that runs in the background."""

    graph_interval = GraphInterval.Daily
    page = Page.Homepage

    while True:
        if button_x.read():
            # TODO: change the graph interval

            if page is Page.Homepage:
                if graph_interval is GraphInterval.Daily:
                    graph_interval = GraphInterval.Weekly
                elif graph_interval is GraphInterval.Weekly:
                    graph_interval = GraphInterval.Monthly
                elif graph_interval is GraphInterval.Monthly:
                    graph_interval = GraphInterval.Daily

                print("Graph interval changed")
                render_homepage(last_sensor, graph_interval)

        if button_y.read():
            # TODO: go to settings, back etc

            if page is Page.Homepage:
                page = Page.Settings
                print("Settings page opened")
            elif page is Page.Settings:
                page = Page.Homepage
                print("Homepage opened")

        if button_a.read():
            # TODO: change the sensor to previous one
            pass
        if button_b.read():
            # TODO: change the sensor to next one
            pass

        if page is Page.Homepage:
            render_homepage(last_sensor, graph_interval)
        elif page is Page.Settings:
            render_settings()

        time.sleep(0.1)


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

    _thread.start_new_thread(main_task, ())

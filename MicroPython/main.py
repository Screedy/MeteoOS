import time
import _thread

from config.config import *
# import graphics.graphics_text
import graphics.graphics
import page_elements
import temp_sensor
# from homepage import homepage_loop
import pages.settings as settings
from config.startup import startup
from sensors.sensor_manager import SensorManager
from graphics.graph import ContextGraphInterval, GraphInterval, ConcreteStrategyDaily, ConcreteStrategyWeekly
from machine import RTC


def render_homepage(graph_interval):
    """Renders the homepage with information about the selected sensor and selected graph interval.

    :param graph_interval: The selected graph interval. Either 1 (Hourly), 2 (Daily), 3 (Weekly) or 4 (Monthly).
    :return: None
    """

    display = Display()
    graph = ContextGraphInterval()
    sensor_manager = SensorManager()

    page_elements.clear_fast()
    display().set_pen(Colors.WHITE)

    page_elements.render_homepage_buttons(graph_interval)
    page_elements.render_nav_arrows(6)
    page_elements.render_sensor_details()
    display().line(101, 16, 101, 120, 3)

    active_sensor = sensor_manager.sensors[sensor_manager.active_sensor]
    graph.render_graph((2024, 2, 15, 2), active_sensor, False)

    display().update()


def main_task():
    """The main task that runs in the background."""

    graph_interval = GraphInterval.Daily
    sensor_manager = SensorManager()
    sensor = 0

    while True:     # Homepage loop
        if button_x.read():
            # TODO: change the graph interval

            if graph_interval is GraphInterval.Daily:
                graph_interval = GraphInterval.Weekly
            elif graph_interval is GraphInterval.Weekly:
                graph_interval = GraphInterval.Monthly
            elif graph_interval is GraphInterval.Monthly:
                graph_interval = GraphInterval.Daily

            print("Graph interval changed")

        if button_y.read():
            print("Opening settings")
            settings.settings_loop()
            print("Settings closed, back to homepage")

        if button_a.read():
            sensor_manager.next_sensor()

        if button_b.read():
            sensor_manager.previous_sensor()

        render_homepage(graph_interval)
        time.sleep(0.5)


if __name__ == "__main__":
    startup()

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

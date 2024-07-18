from utime import sleep, ticks_diff, ticks_us
from _thread import start_new_thread
from gc import collect, mem_free


from config.config import Colors, button_x, button_y, button_a, button_b, Display, GraphInterval
from config.startup import startup
from config.env import env_vars
from graphics.graph_strategy.context_graph_interval import ContextGraphInterval
from graphics import page_elements
import pages.settings as settings
from sensors.sensor_manager import SensorManager


def render_homepage(graph_interval):
    """Renders the homepage with information about the selected sensor and selected graph_strategy interval.

    :param graph_interval: The selected graph_strategy interval. Either 1 (Hourly), 2 (Daily), 3 (Weekly) or 4 (Monthly).
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
    graph.render_graph((2024, 2, 15, 3), active_sensor, False)

    display().update()

    if env_vars['TEST_HOMEPAGE_MEMORY']:
        return mem_free()


def main_task():
    """The main task that runs in the background."""

    graph_interval = GraphInterval.Daily
    sensor_manager = SensorManager()

    while True:     # Homepage loop
        if button_x.read():
            # TODO: change the graph_strategy interval

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

        if env_vars['TEST_HOMEPAGE']:
            start = ticks_us()
            render_homepage(graph_interval)
            end = ticks_us()
            diff = ticks_diff(end, start) / 1_000_000

            display = Display()
            page_elements.clear_fast()
            display().set_pen(Colors.RED)
            display().text(f"Render time: {diff:.5f} s", 2, 2, 236, 2)
            display().update()
            sleep(2)
        elif env_vars['TEST_HOMEPAGE_MEMORY']:
            before_gc_collect = mem_free()
            collect()
            start_mem = mem_free()
            end_mem = render_homepage(graph_interval)
            diff_mem = start_mem - end_mem

            display = Display()
            page_elements.clear_fast()
            display().set_pen(Colors.RED)
            display().text(f"Memory before: {start_mem} B", 2, 2, 236, 2)
            display().text(f"Memory after: {end_mem} B", 2, 20, 236, 2)
            display().text(f"Memory diff: {diff_mem} B", 2, 40, 236, 2)
            display().text(f"Bef collect: {before_gc_collect} B", 2, 60, 236, 2)
            display().update()
            sleep(2)
        else:
            render_homepage(graph_interval)

        sleep(0.5)


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

    collect()
    start_new_thread(main_task, ())

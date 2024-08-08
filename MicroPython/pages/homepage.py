from time import localtime
from gc import mem_free
from graphics.graph_strategy.context_graph_interval import ContextGraphInterval
from graphics import page_elements
from config.config import Display, Colors
from sensors.sensor_manager import SensorManager
from config.env import env_vars


def render_homepage(graph_interval):
    """Renders the homepage with information about the selected sensor and selected graph_strategy interval.

    :param graph_interval: The selected graph_strategy interval. Either 1 (Hourly), 2 (Daily), 3 (Weekly) or 4 (Monthly).
    :return: None
    """

    display = Display()
    graph = ContextGraphInterval()
    graph.strategy = graph_interval
    sensor_manager = SensorManager()

    page_elements.clear_fast()
    display().set_pen(Colors.WHITE)

    page_elements.render_homepage_buttons(graph_interval)
    page_elements.render_nav_arrows(6)
    page_elements.render_sensor_details()
    display().line(101, 16, 101, 120, 3)

    if len(sensor_manager.sensors) == 0:
        display().update()
        return

    active_sensor = sensor_manager.sensors[sensor_manager.active_sensor]
    # Value is fixed here to test on same data every time.
    # graph.render_graph((2024, 2, 15, 3), active_sensor, False)

    if active_sensor:
        current_time = localtime()
        graph.render_graph((current_time[0], current_time[1], current_time[2], current_time[6]), active_sensor, False)

    display().update()

    if env_vars['TEST_HOMEPAGE_MEMORY']:
        return mem_free()

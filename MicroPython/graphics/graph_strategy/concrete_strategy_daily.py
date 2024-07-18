import gc
import os
import utime

from config.sdcard_manager import SDCardManager
import sensors.sensor_manager as sm
from config.config import singleton, Colors, GraphInterval, Display
from config.env import env_vars
from graphics.graph_strategy.strategy_graph_interval import StrategyGraphInterval
from graphics.graph_strategy.graph_utils import days_data, get_measurements, render_temp_values
from utils.sensor_calculations import temperature_to_pixel, get_max_min


class ConcreteStrategyDaily(StrategyGraphInterval):
    """The concrete strategy for rendering the daily graph_strategy."""

    def render_graph(self, date, target_sensor, force) -> None:
        """Renders the daily graph_strategy using the strategy pattern.

        :param date: The day to referer the week to. If set to Friday 16th of the month, the graph_strategy will
        display a week from 12th to 18th.
        :param target_sensor: The sensor to get the data from.
        :param force: If set to True, the graph_strategy will be rendered from the file again and not from memory.
        :return: None
        """

        disp = Display()
        start_time, end_time = 0, 0

        disp().text("MO TU WE TH FR SA SU", 130, 105, 250, 1)

        if force:
            if env_vars['TEST_GRAPH']:
                start_time = utime.ticks_us()
            elif env_vars['TEST_GRAPH_MEMORY']:
                gc.collect()
                # ram_before = gc.mem_free()
                # print("RAM before loading the data:", ram_before)

            temp, hum = days_data(date, target_sensor)

            with open("/sensors/measurements/" + target_sensor.name + "daily.txt", "w") as fw:
                fw.write(f"{temp};{hum}")
        else:
            temp, hum = get_measurements(target_sensor)

        render_daily_graph((list(temp)), list(hum))

        if force and env_vars['TEST_GRAPH']:
            end_time = utime.ticks_us()
            print("Time to render the graph_strategy during full generation:",
                  utime.ticks_diff(end_time, start_time) / 1_000_000)


def render_daily_graph(temperatures, humidity):
    disp = Display()
    max_temp, min_temp, max_hum, min_hum = get_max_min(temperatures, humidity)
    render_temp_values(max_temp, min_temp, max_hum, min_hum)

    for i in range(6):
        if temperatures[i] != -404 and temperatures[i + 1] != -404:
            disp().line(130 + i * 16, int(temperature_to_pixel(temperatures[i], max_temp, min_temp)),
                        130 + (i + 1) * 16, int(temperature_to_pixel(temperatures[i + 1], max_temp, min_temp)), 2)
            continue

        if temperatures[i] != -404:
            disp().pixel(130 + i * 16, int(temperature_to_pixel(temperatures[i], max_temp, min_temp)))

        if temperatures[i + 1] != -404:
            disp().pixel(130 + (i + 1) * 16, int(temperature_to_pixel(temperatures[i + 1], max_temp, min_temp)))

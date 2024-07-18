from config.config import Display
from graphics.graph_strategy.strategy_graph_interval import StrategyGraphInterval
from graphics.graph_strategy.graph_utils import get_measurements, render_temp_values, week_data
from utils.sensor_calculations import get_max_min, temperature_to_pixel


class ConcreteStrategyWeekly(StrategyGraphInterval):
    """The concrete strategy for rendering the weekly graph_strategy."""

    def render_graph(self, date, target_sensor, force) -> None:
        """Renders the weekly graph_strategy using the strategy pattern.

        :param date: The day to referer the month to. If set to 16th of January, the graph_strategy will be
        displayed from 1st to 31st of January.
        :param target_sensor: The sensor to get the data from.
        :param force: If set to True, the graph_strategy will be rendered from the file again and not from memory.
        :return: None
        """

        disp = Display()

        disp().text("WEEK1 WEEK2 WEEK3 WEEK4", 130, 105, 250, 1)

        if force:
            temp, hum = week_data(date, target_sensor)

            with open("/sensors/measurements/" + target_sensor.name + "weekly.txt", "w") as fw:
                fw.write(f"{temp};{hum}")
        else:
            temp, hum = get_measurements(target_sensor)

        render_weekly_graph((list(temp)), list(hum))


def render_weekly_graph(temperatures, humidity):
    disp = Display()
    max_temp, min_temp, max_hum, min_hum = get_max_min(temperatures, humidity)
    render_temp_values(max_temp, min_temp, max_hum, min_hum)

    for i in range(3):
        if temperatures[i] != -404 and temperatures[i + 1] != -404:
            disp().line(130 + i * 32, int(temperature_to_pixel(temperatures[i], max_temp, min_temp)),
                        130 + (i + 1) * 32, int(temperature_to_pixel(temperatures[i + 1], max_temp, min_temp)), 2)
            continue

        if temperatures[i] != -404:
            disp().pixel(130 + i * 32, int(temperature_to_pixel(temperatures[i], max_temp, min_temp)))

        if temperatures[i + 1] != -404:
            disp().pixel(130 + (i + 1) * 32, int(temperature_to_pixel(temperatures[i + 1], max_temp, min_temp)))

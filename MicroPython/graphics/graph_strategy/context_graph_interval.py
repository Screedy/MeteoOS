import gc
import os
import utime

from config.sdcard_manager import SDCardManager
import sensors.sensor_manager as sm
from config.config import singleton, Colors, GraphInterval, Display
from config.env import env_vars
from graphics.graph_strategy.strategy_graph_interval import StrategyGraphInterval
from graphics.graph_strategy.concrete_strategy_daily import ConcreteStrategyDaily


@singleton
class ContextGraphInterval:
    """The context class for the strategy pattern to render the graphs."""

    _strategy = None

    def __init__(self, strategy=ConcreteStrategyDaily()) -> None:
        """Initializes the context class with the strategy.

        :param strategy: The strategy to use for rendering the graph_strategy.
        """

        self._strategy = strategy

    @property
    def strategy(self):
        """The strategy to use for rendering the graph_strategy."""

        return self._strategy

    @strategy.setter
    def strategy(self, strategy: StrategyGraphInterval) -> None:
        """Sets the strategy to use for rendering the graph_strategy."""

        self._strategy = strategy

    def render_graph(self, date, target_sensor, force) -> None:
        """Renders the graph_strategy using the strategy pattern."""

        disp = Display()

        disp().set_pen(Colors.WHITE)

        is_loaded = True

        strategy_str = str(self.strategy)[17]

        if strategy_str == "D":
            try:
                os.stat("/sensors/measurements/" + target_sensor.name + "daily.txt")
            except OSError:
                is_loaded = False

        if strategy_str == "W":
            try:
                os.stat("/sensors/measurements/" + target_sensor.name + "weekly.txt")
            except OSError:
                is_loaded = False

        if not is_loaded:
            force = True

        disp().line(125, 103, 234, 103, 1)
        disp().line(125, 103, 125, 20, 1)

        self._strategy.render_graph(date, target_sensor, force)

        disp().update()

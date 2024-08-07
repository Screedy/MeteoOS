from uos import stat

from config.config import singleton, Colors, Display, GraphInterval
from graphics.graph_strategy.concrete_strategy_daily import ConcreteStrategyDaily
from graphics.graph_strategy.concrete_strategy_weekly import ConcreteStrategyWeekly


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
    def strategy(self, strategy: GraphInterval) -> None:
        """Sets the strategy to use for rendering the graph_strategy."""

        if strategy == GraphInterval.Daily:
            self._strategy = ConcreteStrategyDaily()
        elif strategy == GraphInterval.Weekly:
            self._strategy = ConcreteStrategyWeekly()
        else:
            self._strategy = ConcreteStrategyDaily()    # Default to daily

    def render_graph(self, date, target_sensor, force) -> None:
        """Renders the graph_strategy using the strategy pattern."""

        disp = Display()

        disp().set_pen(Colors.WHITE)

        is_loaded = True

        strategy_str = str(self.strategy)[17]

        if strategy_str == "D":
            try:
                stat("/sensors/measurements/" + target_sensor.name + "daily.txt")
            except OSError:
                is_loaded = False

        if strategy_str == "W":
            try:
                stat("/sensors/measurements/" + target_sensor.name + "weekly.txt")
            except OSError:
                is_loaded = False

        if not is_loaded:
            force = True

        disp().line(125, 103, 234, 103, 1)
        disp().line(125, 103, 125, 20, 1)

        self._strategy.render_graph(date, target_sensor, force)

        disp().update()

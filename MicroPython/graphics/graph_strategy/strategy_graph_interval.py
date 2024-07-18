
class StrategyGraphInterval:
    """The strategy interface for rendering the graph_strategy."""

    def render_graph(self, date, target_sensor, force) -> None:
        """Renders the graph_strategy using the strategy pattern.

        :param date: The day to reference the graph_strategy to.
        :param target_sensor: The sensor to get the data from.
        :param force: If set to True, the graph_strategy will be rendered from the file again and not from memory.
        """

        pass

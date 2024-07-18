import sensors.sensor_manager as sm
from config.config import Colors, Display
from graphics.graph_strategy.concrete_strategy_daily import ConcreteStrategyDaily, render_daily_graph
from graphics.graph_strategy.context_graph_interval import ContextGraphInterval
from graphics.graph_strategy.concrete_strategy_weekly import ConcreteStrategyWeekly
from graphics.graph_strategy.graph_utils import days_data

if __name__ == "__main__":
    from utime import sleep
    display = Display()

    sensor_manager = sm.SensorManager()
    sensor = sensor_manager.sensors[0]

    temp, hum = days_data((2024, 2, 15, 3), sensor)
    temp = [22.25736, 23.50342, 23.37879, 22.43661, 24.4356, 20.3456, 23.4464]
    hum = [35.8522, 32.9066, 33.10038, 35.83953, -404, -404, -404]
    print(temp, hum)

    render_daily_graph(temp, hum)

    graph = ContextGraphInterval(ConcreteStrategyDaily())
    graph.render_graph((2024, 2, 15, 3), sensor, True)
    print("Graph rendered")
    graph.render_graph((2024, 2, 15, 3), sensor, False)
    print("Graph rendered again from memory.")

    graph = ContextGraphInterval(ConcreteStrategyWeekly())
    graph.render_graph((2024, 2, 15, 3), sensor, True)
    print("Graph rendered")
    graph.render_graph((2024, 2, 15, 3), sensor, False)
    print("Graph rendered again from memory.")

    sleep(5)
    # page_elements.clear_fast()

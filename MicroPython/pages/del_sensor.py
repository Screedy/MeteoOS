import time
from config.config import *
from sensors.sensor_manager import SensorManager, AvailableSensors
import page_elements
from sensors.dht11 import DHT11


def render_del_sensor():
    """Renders the page for deleting a sensor."""

    selected_sensor = select_sensor()
    if selected_sensor is None:
        return

    sensors = SensorManager()
    sensors.remove_sensor(selected_sensor)


def select_sensor():
    """Selects the sensor to delete

    :return: The ID of a selected sensor
    """

    display = Display()

    sensor_list = SensorManager().sensors
    sensor_list_length = len(sensor_list)
    selected_sensor = 0

    while True:
        if button_a.read():
            selected_sensor = (selected_sensor + 1) % sensor_list_length

        if button_b.read():
            selected_sensor = (selected_sensor - 1) % sensor_list_length

        if button_x.read():
            return int(sensor_list[selected_sensor].pin)

        if button_y.read():
            return None

        page_elements.clear_fast()
        display().set_pen(Colors.WHITE)
        selected = sensor_list[selected_sensor]
        display().text(f"Select the sensor you want to delete: GP{selected.pin} - {selected.name}", 2, 0, 200, 2)
        display().update()
        time.sleep(0.1)


if __name__ == "__main__":
    render_del_sensor()

from utime import sleep

from config.config import Display, Colors
from config.buttons import button_a, button_b, button_x, button_y
from sensors.sensor_manager import SensorManager
from graphics import page_elements
from graphics.graphics import draw_confirm, draw_cancel


def render_del_sensor():
    """Renders the page for deleting a sensor."""

    selected_sensor = select_sensor()
    if selected_sensor is None:
        return False

    sensors = SensorManager()
    sensors.remove_sensor(selected_sensor)

    return True


def select_sensor():
    """Selects the sensor to delete

    :return: The ID of a selected sensor
    """

    display = Display()

    sensor_list = SensorManager().sensors
    sensor_list_length = len(sensor_list)
    selected_sensor = 0

    sensor_names = [sensor.name for sensor in sensor_list]

    while True:
        sleep(0.1)

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
        page_elements.render_nav_arrows(110)
        display().text(f"Select the sensor you want to delete. Data will remain saved.", 2, 0, 90, 2)
        page_elements.render_items_list(selected_sensor, sensor_names)

        draw_confirm()
        draw_cancel()

        display().update()


if __name__ == "__main__":
    render_del_sensor()

import time
from config.config import *
from sensors.sensor_manager import SensorManager, AvailableSensors
import page_elements
from sensors.dht11 import DHT11


def render_add_sensor():
    """Renders the page for adding a new sensor."""

    display = Display()

    page_elements.clear_fast()

    display().set_pen(Colors.WHITE)
    display().text("Add new sensor", 2, 0, 236, 2)

    selected_sensor = select_sensor_type()
    if selected_sensor is None:
        return

    selected_pin = select_sensor_pin()
    if selected_pin is None:
        return

    selected_name = select_sensor_name()
    if selected_name is "":
        return

    selected_interval = select_interval()
    if selected_interval is None:
        return

    sensors = SensorManager()
    sensors.add_sensor(DHT11(selected_pin, selected_name, selected_interval))


def select_sensor_type():
    """Selects the sensor type

    :return: The selected sensor type.
    """

    display = Display()

    sensor_list = AvailableSensors.list_sensors()
    sensor_list_length = len(sensor_list)
    selected_sensor = 0

    while True:
        if button_a.read():
            selected_sensor = (selected_sensor + 1) % sensor_list_length

        if button_b.read():
            selected_sensor = (selected_sensor - 1) % sensor_list_length

        if button_x.read():
            return sensor_list[selected_sensor]

        if button_y.read():
            return None

        page_elements.clear_fast()
        display().set_pen(Colors.WHITE)
        display().text(f"Select the sensor type: {sensor_list[selected_sensor]}", 2, 20, 200, 2)
        display().update()
        time.sleep(.15)


def select_sensor_pin():
    """Selects the sensor pin

    :return: The selected sensor pin.
    """

    display = Display()

    pin_list = SensorManager().load_available_pins()
    pin_list_length = len(pin_list)
    selected_pin = 0

    while True:
        if button_a.read():
            selected_pin = (selected_pin + 1) % pin_list_length

        if button_b.read():
            selected_pin = (selected_pin - 1) % pin_list_length

        if button_x.read():
            return int(pin_list[selected_pin][2])

        if button_y.read():
            return None

        page_elements.clear_fast()
        display().set_pen(Colors.WHITE)
        display().text(f"Select the sensor pin: {pin_list[selected_pin]}", 2, 20, 236, 2)
        display().update()
        time.sleep(.15)


def select_sensor_name():
    """Name the sensor. Max 6 character long name.

    :return: The name of the sensor.
    """

    display = Display()
    name = ""

    current_ascii = 65

    while True:
        if button_a.read():
            current_ascii = (current_ascii + 1) % 91
            if current_ascii == 0:
                current_ascii = 65

        if button_b.read():
            current_ascii = (current_ascii - 1) % 91
            if current_ascii == 64:
                current_ascii = 90

        if button_x.read():
            if len(name) < 6:
                name = name + chr(current_ascii)
                current_ascii = 65
            else:
                return name

        if button_y.read():
            return name

        page_elements.clear_fast()
        display().set_pen(Colors.WHITE)
        display().text(f"Name of the sensor:", 2, 20, 236, 2)
        display().text(name, 2, 40, 236, 2)
        length = display().measure_text(name, 2) + 2
        display().text(chr(current_ascii), length, 40, 236, 2)

        display().update()
        time.sleep(.15)


def select_interval():
    """Selects the graph interval.

    :return: The selected graph interval.
    """

    display = Display()
    interval_time = 0

    display().set_pen(Colors.WHITE)

    while True:
        if button_a.read():
            interval_time += 1

        if button_b.read():
            interval_time -= 1 if interval_time > 0 else 0

        if button_x.read():
            return interval_time

        if button_y.read():
            return None

        page_elements.clear_fast()
        display().set_pen(Colors.WHITE)
        display().text(f"Select the refresh interval of the sensor", 2, 20, 236, 2)
        display().text(f"Interval: {interval_time} s", 2, 40, 236, 2)
        display().update()
        time.sleep(.15)


if __name__ == "__main__":
    # select_sensor_name()
    # select_sensor_pin()
    # select_sensor_type()
    render_add_sensor()
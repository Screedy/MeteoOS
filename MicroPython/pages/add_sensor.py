from utime import sleep
from config.config import Colors, Display
from config.buttons import button_a, button_b, button_x, button_y
from sensors.sensor_manager import SensorManager, AvailableSensors
from graphics import page_elements
from sensors.dht11 import DHT11
from graphics.graphics import draw_next, draw_confirm, draw_cancel, draw_back


def render_add_sensor():
    """Renders the page for adding a new sensor."""

    display = Display()

    page_elements.clear_fast()

    display().set_pen(Colors.WHITE)
    display().text("Add new sensor", 2, 0, 236, 2)

    selected_sensor = select_sensor_type()
    if selected_sensor is None:
        return False

    selected_pin = select_sensor_pin()
    if selected_pin is None:
        return False

    selected_name = select_sensor_name()
    if selected_name is "":
        return False

    selected_interval = select_interval()
    if selected_interval is None:
        return False

    sensors = SensorManager()
    sensors.add_sensor(DHT11(selected_pin, selected_name, selected_interval))

    return True


def select_sensor_type():
    """Selects the sensor type

    :return: The selected sensor type.
    """

    display = Display()

    sensor_list = AvailableSensors.list_sensors()
    sensor_list_length = len(sensor_list)
    selected_sensor = 0

    while True:
        sleep(.1)
        if button_a.is_held():
            selected_sensor = (selected_sensor + 1) % sensor_list_length

        if button_b.is_held():
            selected_sensor = (selected_sensor - 1) % sensor_list_length

        if button_x.read():
            return sensor_list[selected_sensor]

        if button_y.read():
            return None

        page_elements.clear_fast()
        display().set_pen(Colors.WHITE)
        display().text(f"Select the sensor type: {sensor_list[selected_sensor]}", 2, 20, 170, 2)
        draw_next()
        draw_cancel()
        display().update()


def select_sensor_pin():
    """Selects the sensor pin

    :return: The selected sensor pin.
    """

    display = Display()

    pin_list = SensorManager().load_available_pins()
    pin_list_length = len(pin_list)
    selected_pin = 0

    while True:
        sleep(.1)
        if button_a.is_held():
            selected_pin = (selected_pin + 1) % pin_list_length

        if button_b.is_held():
            selected_pin = (selected_pin - 1) % pin_list_length

        if button_x.read():
            return int(pin_list[selected_pin][2])

        if button_y.read():
            return None

        page_elements.clear_fast()
        display().set_pen(Colors.WHITE)
        display().text(f"Select the sensor pin: {pin_list[selected_pin]}", 2, 20, 180, 2)
        draw_next()
        draw_cancel()
        display().update()


def select_sensor_name():
    """Name the sensor. Max 6 character long name.

    :return: The name of the sensor.
    """

    display = Display()
    characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_"
    len_characters = len(characters)
    name = ""
    current_index = 0

    while True:
        sleep(.1)
        if button_a.is_held():
            current_index = (current_index + 1) % len_characters
        elif button_b.is_held():
            current_index = (current_index - 1) % len_characters
        elif button_x.read():
            if len(name) < 6:
                name += (characters[current_index]) if characters[current_index] != "_" else " "
                current_ascii = 0
            else:
                return name.rstrip()

        if button_y.read():
            if len(name) > 0:
                name = name[:-1]
            else:
                return ""

        page_elements.clear_fast()
        display().set_pen(Colors.WHITE)
        display().text(f"Name of the sensor:", 2, 20, 180, 2)
        display().text(name, 2, 50, 236, 2)
        draw_next()

        if len(name) > 0:
            draw_back()
        else:
            draw_cancel()
        length = display().measure_text(name, 2) + 2
        display().set_pen(Colors.GREY)
        display().text(characters[current_index], length, 50, 236, 2)

        display().update()


def select_interval():
    """Selects the graph_strategy interval.

    :return: The selected graph_strategy interval.
    """

    display = Display()
    interval_time = 0

    display().set_pen(Colors.WHITE)

    while True:
        sleep(.1)
        if button_a.is_held():
            interval_time += 1

        if button_b.is_held():
            interval_time -= 1 if interval_time > 0 else 0

        if button_x.read():
            return interval_time * 60

        if button_y.read():
            return None

        page_elements.clear_fast()
        display().set_pen(Colors.WHITE)
        display().text(f"Select the refresh interval of the sensor", 2, 20, 150, 2)
        display().text(f"Interval: {interval_time} m", 2, 80, 236, 2)
        draw_confirm()
        draw_cancel()
        display().update()


if __name__ == "__main__":
    # select_sensor_name()
    # select_sensor_pin()
    # select_sensor_type()
    # select_interval()
    render_add_sensor()

from config.config import singleton
from sensors.dht11 import DHT11


@singleton
class SensorManager:
    """A singleton class for managing all sensors connected to the Pico."""

    _sensors: list
    _active_sensor: int
    _available_pins: list

    def __init__(self):
        """Initializes the sensor manager.

        :raise OSError: If the file sensors.txt does not exist, it will be created.
        :return: None
        """
        self._sensors = None

        self._sensors = self.load_sensors()
        self._active_sensor = 0
        self._available_pins = self.load_available_pins()

    def load_sensors(self):
        """Loads the sensors from the file sensors.txt.

        :return: A list of sensors
        """

        fr_sensors = None

        if self.sensors is not None:
            return self.sensors

        try:
            fr_sensors = open("sensors.txt", "r")

            sensors = []
            for line in fr_sensors.readlines():
                line = line.split(";")
                sensors.append(DHT11(int(line[0]), line[1], int(line[2])))

        except OSError:
            fr_sensors = open("sensors.txt", "w")
            return []

        finally:
            fr_sensors.close()

        return sensors

    @staticmethod
    def load_available_pins():
        """Loads the available pins according to the file sensors.txt.

        :return: A list of available pins.
        """

        available_pins = ["GP0", "GP1", "GP9", "GP10", "GP11", "GP20", "GP21", "GP22"]

        fr_sensors = None

        try:
            fr_sensors = open("sensors.txt", "r")

            for line in fr_sensors.readlines():
                line = line.split(";")
                available_pins.remove(f"GP{line[0]}")

        except OSError:
            fr_sensors = open("sensors.txt", "w")
            return available_pins

        finally:
            fr_sensors.close()

        return available_pins

    @property
    def sensors(self):
        """Returns the list of sensors.

        :return: The list of sensors
        """

        return self._sensors

    @property
    def available_pins(self):
        """Returns the list of available pins.

        :return: The list of available pins
        """

        return self._available_pins

    @property
    def active_sensor(self):
        """Returns the index of the active sensor.

        :return: The index of the active sensor.
        """

        if len(self._sensors) <= self._active_sensor:
            self._active_sensor = 0

        return self._active_sensor

    def next_sensor(self):
        """Changes the active sensor to the next one.

        :return: None
        """

        self._active_sensor = (self._active_sensor + 1) % len(self._sensors)

    def previous_sensor(self):
        """Changes the active sensor to the previous one.

        :return: None
        """

        self._active_sensor = (self._active_sensor - 1) % len(self._sensors)

    def add_sensor(self, sensor: DHT11):
        """Adds a sensor to the list of sensors. Also saves the sensor to the file.

        :param sensor: The sensor to add

        :return: None
        """

        self._sensors.append(sensor)

        with open("sensors.txt", "a") as fw_sensors:
            fw_sensors.write(f"{sensor.pin};{sensor.name};{sensor.interval}\n")

    def sensor_list_position(self, pin: int):
        """Returns the position of the sensor in the list of sensors.

        :param pin: The pin of the sensor

        :return: The position of the sensor in the list of sensors or -1 if the sensor is not in the list.
        """

        for sensor in self._sensors:
            if sensor.pin == pin:
                return self._sensors.index(sensor)

        return -1

    def remove_sensor(self, pin: int):
        """Removes a sensor from the list of sensors. Also removes the sensor from the file.

        :param pin: The pin of the sensor to remove

        :return: None
        """

        position = self.sensor_list_position(pin)
        active_sensor_position = self.sensor_list_position(self._active_sensor)

        if position == -1:
            raise ValueError("The given pin is not in the list of sensors.")

        self._sensors.pop(position)

        if position >= active_sensor_position:
            self.next_sensor()

        with open("sensors.txt", "w") as fw_sensors:
            for sensor in self._sensors:
                fw_sensors.write(f"{sensor.pin};{sensor.name};{sensor.interval}\n")

    def pause_measure(self):
        """Pauses the measurement of the active sensor.

        :return: None
        """

        for sensor in self._sensors:
            sensor.pause_measure()

    def resume_measure(self):
        """Resumes the measurement of the active sensor.

        :return: None
        """

        for sensor in self._sensors:
            sensor.resume_measure()


class AvailableSensors:
    """An enum class for listing the available sensors.

    :cvar DHT11: The DHT11 sensor.
    :cvar DS18B20: The DS18B20 sensor.
    """

    DHT11 = 0
    DS18B20 = 1

    @staticmethod
    def list_sensors():
        """Lists the available sensors.

        :return: A list of available sensors
        """

        return [sensor for sensor in AvailableSensors.__dict__.keys() if not sensor.startswith("__") and
                not sensor.startswith("_") and not callable(getattr(AvailableSensors, sensor))]

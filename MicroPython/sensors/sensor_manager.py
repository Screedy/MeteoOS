from config.config import Singleton
from sensors.dht11 import DHT11


@Singleton
class SensorManager:
    """A singleton class for managing all sensors connected to the Pico."""

    _sensors: list
    _available_pins: list

    def __init__(self):
        """Initializes the sensor manager.

        :raise OSError: If the file sensors.txt does not exist, it will be created.
        :return: None
        """

        self._sensors = self.load_sensors()
        self._available_pins = self.load_available_pins()

    @staticmethod
    def load_sensors():
        """Loads the sensors from the file sensors.txt.

        :return: A list of sensors
        """

        fr_sensors = None

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

    def add_sensor(self, sensor: DHT11):
        """Adds a sensor to the list of sensors. Also saves the sensor to the file.

        :param sensor: The sensor to add

        :return: None
        """

        self._sensors.append(sensor)

        with open("sensors.txt", "a") as fw_sensors:
            fw_sensors.write(f"{sensor.pin};{sensor.name};{sensor.interval}\n")

    def remove_sensor(self, pin: int):
        """Removes a sensor from the list of sensors. Also removes the sensor from the file.

        :param pin: The pin of the sensor to remove

        :return: None
        """

        for sensor in self._sensors:
            if sensor.pin == pin:
                self._sensors.remove(sensor)
                break

        with open("sensors.txt", "w") as fw_sensors:
            for sensor in self._sensors:
                fw_sensors.write(f"{sensor.pin};{sensor.name};{sensor.interval}\n")
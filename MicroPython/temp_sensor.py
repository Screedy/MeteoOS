import utime
from machine import Pin, RTC
import dht


class SensorList:
    """Used to store and manage multiple sensors."""

    _sensor_list: list
    _available_pins: list
    _filename: str

    def __init__(self, filename: str = "sensors.txt"):
        """Initializes the sensor list.

        :param filename: The name of the file to load the sensors from. (Default: sensors.txt)
        """

        self._sensor_list = self.load_sensors(filename)
        self._available_pins = self.load_available_pins(filename)
        self._filename = filename

    @staticmethod
    def load_sensors(filename: str = "sensors.txt"):
        """Loads the sensors from a given file.

        :param filename: The name of the file to load the sensors from. (Default: sensors.txt)
        :return: A list of sensors.
        """

        try:
            fr = open(filename, "r")

            sensors = []
            for line in fr.readlines():
                print(line)
                line = line.split(";")
                print(line)
                sensors.append(DHT11(int(line[0]), line[1], int(line[2])))

        except OSError:
            return []

        fr.close()
        return sensors

    @staticmethod
    def load_available_pins(filename: str = "sensors.txt"):
        """Loads the available pins from a given file.

        :param filename: The name of the file which contains the pins used by the sensors. (Default: sensors.txt)
        :return: A list of available pins.
        """

        available_pins = ["GP4", "GP5", "GP9", "GP10", "GP11", "GP20", "GP21", "GP22"]

        try:
            fr = open(filename, "r")

            for line in fr.readlines():
                line = line.split(";")
                available_pins.remove(f"GP{line[0]}")

        except OSError:
            return available_pins

        fr.close()
        return available_pins

    @property
    def sensor_list(self):
        """Returns the sensor list.

        :return: The sensor list
        """

        return self._sensor_list

    @property
    def available_pins(self):
        """Returns the available pins.

        :return: The available pins
        """

        return self._available_pins

    @property
    def filename(self):
        """Returns the filename of the sensor list.

        :return: The filename of the sensor list
        """

        return self._filename

    def add_sensor(self, pin: int, name: str, interval: int = 5):
        """Adds a new sensor to the sensor list.

        :param pin: The pin the sensor is connected to
        :param name: The name of the sensor
        :param interval: The interval of the sensor in seconds. (Default: 5)
        :return: The updated sensor list if the sensor was added successfully.
            Raises a ValueError if the pin is not available.
        """

        if f"GP{pin}" in self._available_pins:
            self._sensor_list.append(DHT11(pin, name, interval))
            self._available_pins.remove(f"GP{pin}")

            try:
                fw = open("sensors.txt", "a")
            except OSError:
                raise OSError("Could not write to sensors.txt")

            fw.write(f"{pin};{name};{interval}\n")
            fw.close()

            return self.load_sensors()

        raise ValueError("The given pin is not available.")

    def remove_sensor(self, sensor_pin: int):
        """Removes a sensor from the sensor list.

        :param sensor_pin: The pin of the sensor to remove
        :return: The updated sensor list if the sensor was removed successfully.
            Raises a ValueError if the sensor was not found.
        """

        for sensor in self._sensor_list:
            if sensor.sensor.pin() == sensor_pin:
                self._sensor_list.remove(sensor)
                self._available_pins.append(f"GP{sensor_pin}")

                with open(self.filename, "r") as fr:
                    with open(self.filename, "w") as fw:
                        for line in fr.readline():
                            if line.split(sep=";")[0] != sensor_pin:
                                fw.write(line)

                return self.load_sensors()

        raise ValueError("The given sensor was not found.")

    def update_sensor_list(self):
        """Updates the sensor list.

        :return: None
        """

        self._sensor_list = self.load_sensors()
        self._available_pins = self.load_available_pins()


class DHT11:
    """DHT11 temperature and humidity sensor"""

    _name: str
    _pin: int
    _sensor: dht.DHT11
    _temperature: float
    _humidity: float
    _interval: int

    def __init__(self, pin: int, name: str, interval: int = 5):
        """Initialize the DHT11 sensor.

        :param pin: The pin the sensor is connected to
        :param name: The name of the sensor
        """

        self._name = name
        self._pin = pin
        self._sensor = dht.DHT11(Pin(pin))
        self._temperature = 0
        self._humidity = 0
        self._interval = interval


    @property
    def name(self):
        """Returns the name of the sensor.

        :return: The name of the sensor
        """

        return self._name

    @name.setter
    def name(self, name: str):
        """Sets the name of the sensor.

        :param name: The name of the sensor
        """

        if 0 < len(str) < 6:
            self._name = name

    @property
    def pin(self):
        """Returns the pin the sensor is connected to.

        :return: The pin the sensor is connected to
        """

        return self._pin

    @pin.setter
    def pin(self, pin: int):
        """Sets the pin the sensor is connected to.

        :param pin: The pin the sensor is connected to
        """

        self._pin = pin

    @property
    def sensor(self):
        """Returns the sensor object.

        :return: The sensor object
        """

        return self._sensor

    @sensor.setter
    def sensor(self, pin: int):
        """Sets the sensor object.

        :param pin: The pin the sensor is connected to
        """

        # TODO: check if pin is valid
        self._sensor = dht.DHT11(Pin(pin))

    @property
    def temperature(self):
        """Measures the temperature and returns it.

        :return: The temperature in °C
        """

        self._sensor.measure()
        self._temperature = self._sensor.temperature()
        return self._temperature

    @property
    def humidity(self):
        """Measures the humidity and returns it.

        :return: The humidity in %
        """

        self._sensor.measure()
        self._humidity = self._sensor.humidity()
        return self._humidity

    @property
    def interval(self):
        """Returns the interval of the sensor in seconds.

        :return: The interval of the sensor
        """

        return self._interval

    @interval.setter
    def interval(self, interval: int):
        """Sets the interval of the sensor in seconds.

        :param interval: The interval of the sensor in seconds. Must be between 0 and 3600.
        :return: True if the interval was set successfully, False if not
        """

        if 0 < interval < 3600:
            self._interval = interval

    def read(self):
        """Reads the sensors data and returns it.

        :return: Returns temperature, humidity and timestring
        """

        self._sensor.measure()
        self._temperature = self._sensor.temperature()
        self._humidity = self._sensor.humidity()

        return self._temperature, self._humidity

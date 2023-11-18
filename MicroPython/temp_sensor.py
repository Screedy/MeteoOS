import utime
from machine import Pin, RTC
import dht


class DHT11:
    """DHT11 temperature and humidity sensor"""

    _name: str
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
        self._sensor = dht.DHT11(Pin(pin))
        self._temperature = 0
        self._humidity = 0
        self._interval = interval

    def read(self):
        """Reads the sensors data and returns it.

        :return: Returns temperature, humidity and timestring
        """

        self._sensor.measure()
        self._temperature = self._sensor.temperature()
        self._humidity = self._sensor.humidity()

        return self._temperature, self._humidity

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

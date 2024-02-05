from machine import Pin
import ds18x20
import onewire


class DS18B20:
    """Class managing the DS18B20 sensor"""

    def __init__(self, pin: int, name: str):
        """Class managing the DS18B20 sensor

        :param pin: The pin of the sensor
        :param name: The name of the sensor
        """

        self._name = name
        self._pin = Pin(pin)
        self._sensor = ds18x20.DS18X20(onewire.OneWire(Pin(pin)))
        self._sensor_type = "DS18B20"
        self._roms = self._sensor.scan()

    @property
    def name(self):
        """Returns the name of the sensor"""

        return self._name

    @name.setter
    def name(self, name: str):
        """Sets the name of the sensor

        :param name: The name of the sensor
        :returns: None"""

        self._name = name

    @property
    def pin(self):
        """Returns the pin of the sensor"""

        return self._pin

    @pin.setter
    def pin(self, pin: int):
        """Changes the pin of the sensor and reinitialized it

        :param pin: The new pin for the sensor
        """

        self._pin = Pin(pin)
        self._sensor = ds18x20.DS18X20(self._pin)

    @property
    def roms(self):
        """Returns the roms of the sensors"""

        return self._roms

    @property
    def sensor_type(self):
        """Returns the sensor type"""

        return self._sensor_type

    def measure(self):
        """Returns the temperature in Celsius"""

        self._sensor.convert_temp()
        return self._sensor.read_temp(self._roms[0])
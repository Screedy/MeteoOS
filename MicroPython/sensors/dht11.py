import utime
from machine import Pin, RTC, Timer
import dht
from config.sdcard_manager import SDCardManager


class DHT11:
    """DHT11 temperature and humidity sensor"""

    _name: str
    _pin: int
    _sensor: dht.DHT11
    _temperature: float
    _humidity: float
    _interval: int
    _timer: Timer
    _write: bool

    def __init__(self, pin: int, name: str, interval: int = 5):
        """Initialize the DHT11 sensor.

        :param pin: The pin the sensor is connected to
        :param name: The name of the sensor
        :param interval: The interval of the sensor in seconds. Must be between 0 and 3600.
        """

        self._name = name
        self._pin = pin
        self._sensor = dht.DHT11(Pin(pin))
        self._temperature = 0
        self._humidity = 0
        self._interval = interval

        # _thread.start_new_thread(self.measure, ())

        # Alternative option using an interrupt
        self._timer = Timer(mode=Timer.PERIODIC, period=1000 * interval, callback=self.measure)
        self._write = True

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
        """Returns the temperature measured in the given interval.

        :return: The temperature in °C
        """

        return self.sensor.temperature()

    @property
    def humidity(self):
        """Returns the humidity measured in the given interval.

        :return: The humidity in %
        """

        return self.sensor.humidity()

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

    @property
    def write(self):
        """Returns the write to file status.

        :return: The write to file status
        """

        return self._write

    @write.setter
    def write(self, write_to_file: bool):
        """Sets the write to file status.

        :param write_to_file: The write to file status
        """

        self._write = write_to_file

    def measure(self, timer):
        """Measures the temperature and humidity in the given interval.

        :param timer: The timer object
        :return: None
        """

        self._sensor.measure()
        self.write_to_file()

    def write_to_file(self):
        """Writes the sensor data to a file.

        :return: None
        """

        if not self.write:
            return

        print("Writing to file")
        if RTC().datetime()[0] < 2022:
            print("RTC not set, unable to write to file")
            return

        sd = SDCardManager()
        if not sd.is_mounted:
            try:
                sd.mount()
            except OSError as e:
                print(f"Failed to mount SD card: {e}, unable to write to file")
                return

        with open("sd/measurements/" + self.name+".txt", "a") as fw_sensor:
            fw_sensor.write(f"{RTC().datetime()};{self.temperature};{self.humidity}\n")

    def pause_measure(self):
        """Pauses the measurement of the sensor.

        :return: None
        """

        self.write = False

    def resume_measure(self):
        """Resumes the measurement of the sensor.

        :return: None
        """

        self.write = True


if __name__ == "__main__":
    sensor = DHT11(0, "DHT11", 5)

    while True:
        print(f"Time: {RTC().datetime()}")
        print(f"Temperature: {sensor.temperature}°C, Humidity: {sensor.humidity}%")
        utime.sleep(2.5)

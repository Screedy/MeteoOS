from machine import Pin, SPI
import os
from config.config import singleton
import sdcard


@singleton
class SDCard:
    """Singleton class managing the SD card"""

    _spi = None

    _baudrate = 40000000
    _sck = Pin(2)
    _mosi = Pin(3)
    _miso = Pin(4)
    _cs = Pin(5)

    def __init__(self):
        """Initializes the SD card"""

        self._spi = SPI(0, baudrate=self._baudrate, sck=self._sck, mosi=self._mosi, miso=self._miso)

    def mount(self):
        """Mounts the SD card as /sd

        :return: True if the SD card was mounted successfully, False otherwise
        """

        try:
            sd = sdcard.SDCard(self._spi, Pin(5))
        except OSError:
            print("SD card was unable to open")
            return False

        cfs = os.VfsFat(sd)
        os.mount(cfs, "/sd")

        return True

    @staticmethod
    def unmount():
        """Unmounts the SD card

        :return: True if the SD card was unmounted successfully, False otherwise
        """

        try:
            os.umount("/sd")
        except OSError:
            print("SD card was unable to unmount")
            return False

        return True

    @property
    def baudrate(self):
        """The baudrate of the SD card

        :return: The baudrate of the SD card
        """

        return self._baudrate

    @baudrate.setter
    def baudrate(self, baudrate: int):
        """Sets the baudrate of the SD card

        :param baudrate: The baudrate of the SD card
        """

        self._baudrate = baudrate
        self._spi.init(baudrate=baudrate)

    @property
    def sck(self):
        """The SCK pin of the SD card

        :return: The SCK pin of the SD card
        """

        return self._sck

    @sck.setter
    def sck(self, sck: Pin):
        """Sets the SCK pin of the SD card

        :param sck: The SCK pin of the SD card
        """

        self._sck = sck
        self._spi.init(sck=sck)     # TODO: check for only correct pins

    @property
    def mosi(self):
        """The MOSI pin of the SD card

        :return: The MOSI pin of the SD card
        """

        return self._mosi

    @mosi.setter
    def mosi(self, mosi: Pin):
        """Sets the MOSI pin of the SD card

        :param mosi: The MOSI pin of the SD card
        """

        self._mosi = mosi
        self._spi.init(mosi=mosi)     # TODO: check for only correct pins

    @property
    def miso(self):
        """The MISO pin of the SD card

        :return: The MISO pin of the SD card
        """

        return self._miso

    @miso.setter
    def miso(self, miso: Pin):
        """Sets the MISO pin of the SD card

        :param miso: The MISO pin of the SD card
        """

        self._miso = miso
        self._spi.init(miso=miso)     # TODO: check for only correct pins

    @property
    def cs(self):
        """The CS pin of the SD card

        :return: The CS pin of the SD card
        """

        return self._cs

    @cs.setter
    def cs(self, cs: Pin):
        """Sets the CS pin of the SD card

        :param cs: The CS pin of the SD card
        """

        self._cs = cs
        self._spi.init(cs=cs)     # TODO: check for only correct pins

    @property
    def spi(self):
        """The SPI object of the SD card

        :return: The SPI object of the SD card
        """

        return self._spi

    @staticmethod
    def is_mounted():
        """Checks if the SD card is mounted.

        :return: True if the SD card is mounted, False otherwise
        """

        return "/sd" in os.listdir("/")

    def format_sd(self):
        """Formats the SD card."""

        if self.is_mounted():
            os.mkfs("/sd")

            return True

        print("SD card is not mounted or not accessible")
        return False

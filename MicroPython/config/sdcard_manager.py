from machine import Pin, SPI
from uos import VfsFat, mount, umount, listdir, chdir, remove

from config.config import singleton
import sdcard
from config.env import env_vars
from utils.decorators import execution_time


@singleton
class SDCardManager:
    """Singleton class managing the SD card"""

    _spi = None

    _baudrate = 40000000
    _sck = Pin(10)
    _mosi = Pin(11)
    _miso = Pin(8)
    _cs = Pin(9, Pin.OUT)

    def __init__(self):
        """Initializes the SD card"""

        self._spi = SPI(1, baudrate=self._baudrate, sck=self._sck, mosi=self._mosi, miso=self._miso)

    def mount(self):
        """Mounts the SD card as /sd

        :return: True if the SD card was mounted successfully, False otherwise
        """

        try:
            target_sd = sdcard.SDCard(self._spi, self._cs)
            vfs = VfsFat(target_sd)
            mount(vfs, "/sd")
        except OSError:
            print("SD card was unable to open during mount procedure.")
            return False

        return True

    @staticmethod
    def unmount():
        """Unmounts the SD card

        :return: True if the SD card was unmounted successfully, False otherwise
        """

        try:
            umount("/sd")
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
        self._spi.init(sck=sck)  # TODO: check for only correct pins

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
        self._spi.init(mosi=mosi)  # TODO: check for only correct pins

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
        self._spi.init(miso=miso)  # TODO: check for only correct pins

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
        self._spi.init(cs=cs)  # TODO: check for only correct pins

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

        return "sd" in listdir("/")

    def format_sd(self):
        """Formats the SD card."""

        if not self.is_mounted():
            raise OSError("SD card is not mounted")

        # Delete all files on the SD card
        try:
            for file in listdir("/sd"):
                if file.startswith(".") or file == "System Volume Information":
                    continue

                print(f"Removing {file}")
                chdir("/sd")
                remove(file)
        except OSError:
            raise OSError("Error while deleting files on the SD card")
        finally:
            chdir("/")
        return True

    if env_vars["TEST_MEASUREMENT"]:
        @staticmethod
        @execution_time
        def list_files(path="/"):
            return SDCardManager().list_files_body(path)
    else:
        @staticmethod
        def list_files(path="/"):
            return SDCardManager().list_files_body(path)

    @staticmethod
    def list_files_body(path="/"):
        """Lists all files on the SD card.

        :param path: The path to list files from. Default is the root directory.
        :return: A list of all files on the SD card
        """
        return listdir(path)

    @staticmethod
    def delete_file(path):
        """Deletes a file from the SD card.

        :param path: The path of the file to delete.
        :return: True if the file was deleted successfully, False otherwise
        """

        try:
            remove(path)
        except OSError:
            print(f"Error while deleting {path}")
            return False

        return True


if __name__ == "__main__":
    sd = SDCardManager()
    sd.mount()
    print(sd.is_mounted())

    with open("/sd/test.txt", "w") as f:
        f.write("Hello, world!")

    with open("/sd/test.txt", "r") as f:
        print(f.read())

    sd.unmount()

    sd.mount()
    # sd.format_sd()

    for _ in range(10):
        # print(sd.list_files())
        sd.list_files()

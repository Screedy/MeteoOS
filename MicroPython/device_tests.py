"""This file includes all the tests for the devices connected to the Pico."""
from machine import Pin, SPI
import os


def test_storage(spi_controller=0, sck=Pin(2), mosi=Pin(3), miso=Pin(0), cs=Pin(1), verbose=False):
    """
    Tests the SD card storage.
    
    :param spi_controller: The SPI controller to use.
    :param sck: The SCK pin.
    :param mosi: The MOSI pin.
    :param miso: The MISO pin.
    :param cs: The CS pin.
    :param verbose: Whether to print debug information.
    :return: True if the test was successful, False otherwise.
    """

    import sdcard

    spi = SPI(spi_controller, baudrate=40000000, sck=sck,
              mosi=mosi,
              miso=miso)
    try:
        if verbose:
            print("Trying to open SD card")
        sd = sdcard.SDCard(spi, cs)
    except OSError:
        if verbose:
            print("SD card was unable to open")
        return False

    if verbose:
        print("Mounting SD card as /sd")
    cfs = os.VfsFat(sd)
    os.mount(cfs, "/sd")

    # Console print SD card directory with files
    if verbose:
        print("/sd directory: " + str(os.listdir("/sd")))

    if verbose:
        print("Trying to write to SD card")
    fw = open("/sd/test.txt", "w")
    fw.write("Test writing to SD card")
    fw.close()

    if verbose:
        print("Trying to read from SD card")
    fr = open("/sd/test.txt", "r")
    if fr.read() == "Test writing to SD card":
        fr.close()
        os.remove("/sd/test.txt")
        if verbose:
            print("File was sucesfully found and read on the SD card")
        return True

    fr.close()
    if verbose:
        print("File was not found on the SD card")
    os.remove("/sd/test.txt")
    return False


if __name__ == "__main__":
    print("Testing storage")
    print(test_storage())

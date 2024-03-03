import config.config as config
import setup
from config.settings_manager import SettingsManager
from config.sdcard_manager import SDCardManager
from sensors.sensor_manager import SensorManager


def startup():
    """First function to run on boot. Initializes the system."""

    try:
        f = open("settings.txt", "r")
        # continue with the file.
    except OSError:  # open failed (file not found)
        setup.initial()

    sd = SDCardManager()
    sd.mount()

    settings = SettingsManager()    # Initialize the settings manager
    sensor_manager = SensorManager()    # Initialize the sensor manager

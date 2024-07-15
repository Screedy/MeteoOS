import setup
from config.settings_manager import SettingsManager
from config.sdcard_manager import SDCardManager
from sensors.sensor_manager import SensorManager
from graphics.graph import ContextGraphInterval


def startup():
    """First function to run on boot. Initializes the system and checks if the settings file exists.
    If not,  initialize setup."""

    try:
        f = open("settings.txt", "r")   # Check if the settings file exists
        f.close()
    except OSError:  # open failed (file not found)
        setup.initial()

    sd = SDCardManager()
    sd.mount()

    settings = SettingsManager()    # Initialize the settings manager
    sensor_manager = SensorManager()    # Initialize the sensor manager
    graph = ContextGraphInterval()    # Initialize the graph interval

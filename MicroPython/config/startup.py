from config import setup
from config.settings_manager import SettingsManager
from config.sdcard_manager import SDCardManager
from sensors.sensor_manager import SensorManager
from graphics.graph import ContextGraphInterval


def startup():
    """First function to run on boot. Initializes the system and checks if the settings file exists.
    If not,  initialize setup."""

    print("Initializing boot sequence")

    try:
        f = open("settings.txt", "r")   # Check if the settings file exists
        f.close()
    except OSError:  # open failed (file not found)
        setup.initial()

    sd = SDCardManager()
    sd.mount()

    print("SD card mounted")

    settings = SettingsManager()    # Initialize the settings manager

    print("Settings loaded")

    sensor_manager = SensorManager()    # Initialize the sensor manager

    print("Sensors loaded")

    graph = ContextGraphInterval()    # Initialize the graph_strategy interval

    print("Graph loaded")

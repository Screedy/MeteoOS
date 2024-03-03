import config.config as config
import setup
from config.settings_manager import SettingsManager
from config.sdcard_manager import SDCardManager
from sensors.sensor_manager import SensorManager
from graphics.graph import ContextGraphInterval


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
    graph = ContextGraphInterval()    # Initialize the graph interval

    # graph().render_graph((2024, 2, 15, 2), sensor_manager.sensors[sensor_manager.active_sensor], True)
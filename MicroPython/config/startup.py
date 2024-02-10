import config.config as config
import setup
import config.settings_manager.SettingsManager as SettingsManager


def startup():
    """First function to run on boot. Initializes the system."""

    try:
        f = open("settings.txt", "r")
        # continue with the file.
    except OSError:  # open failed (file not found)
        setup.initial()

    settings = SettingsManager()    # Initialize the settings manager

    

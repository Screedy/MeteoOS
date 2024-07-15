#!/bin/sh

# Navigate to the project directory (update the path accordingly)
cd /path/to/MeteoOS/MicroPython

# Download the sdcard.py file from GitHub
curl -O https://raw.githubusercontent.com/micropython/micropython-lib/master/micropython/drivers/storage/sdcard/sdcard.py

# Verify the download
if [ -f "sdcard.py" ]; then
    echo "sdcard.py downloaded successfully."
else
    echo "Failed to download sdcard.py."
fi
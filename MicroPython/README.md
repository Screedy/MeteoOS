## How to install MeteoOS using Thonny IDE
1. Download and install Thonny IDE
	- Go to [thonny.org](https://thonny.org/) and download the version suitable for your operating system (Windows, macOS, or Linux).
2. Flash MicroPython Firmware onto Raspberry Pi Pico
 	- **Download MicroPython with Pimoroni drivers**: Visit [Pimoroni-Pico](https://github.com/pimoroni/pimoroni-pico/releases) and download the latest `.uf2` file (App tested on `v1.20.3`).
	- **Connect Pico to Computer**: Hold down the `BOOTSEL` button on your Pico and connect it to your computer using the micro USB cable. Release the `BOOTSEL` button once connected.
	- **Flash Firmware**: Your Pico will appear as a USB mass storage device. Drag and drop the `.uf2` file onto the Pico’s drive. It will reboot automatically and will now run MicroPython.
3. Set Up Thonny IDE
	- **Open Thonny IDE**: Launch Thonny from your applications menu.
	- **Configure Thonny for Pico**:
		- Go to Tools > Options > Interpreter.
		- Select MicroPython (Raspberry Pi Pico) from the interpreter list.
		- Ensure the correct COM port is selected (Thonny should detect it automatically).
		- Aditionally on **Linux** you might get a error `Unabble to connect to /dev/tty*: [Errno 13]...` in this case you need to add yourself to the Dialout Group.
			```bash
			sudo usermod -a -G dialout $USER
			```
4. Clone the MeteoOS repository and sd card library:
```bash
git clone https://github.com/Screedy/MeteoOS.git
cd MeteoOS/MicroPython/
curl -O https://raw.githubusercontent.com/micropython/micropython-lib/master/micropython/drivers/storage/sdcard/sdcard.py
```
5. Upload and Run MeteoOS
	1. In Thonny, go to File > Open... and navigate to the directory containing your application files.
	2. Select any of the files.
	3. Click the save icon and save it to the Raspberry Pi Pico.
	4. Redo these steps until all files are uploaded. Make sure to mirror the MicroPython directory perfectly.

## How to install MeteoOS using terminal
1. Download and Install Required Tools
	- **Install** **ampy** (you can also use rshell):
```bash
pip install adafruit-ampy
```
    
Check that path to ampy is setup correctly. Simply try `which ampy` in terminal. This should return the path to the ampy executable. If it doesn't, follow these steps:
```bash
python3 -m site --user-base # This will show the user base directory. ampy executable should be located in bin directory.
export PATH=$PATH:/home/screedy/.local/bin # Change the /home/screedy/.local to the path from command above.
```

2. Clone the MeteoOS repository and sd card library:
```bash
git clone https://github.com/Screedy/MeteoOS.git
cd MeteoOS/MicroPython/
curl -O https://raw.githubusercontent.com/micropython/micropython-lib/master/micropython/drivers/storage/sdcard/sdcard.py
```

3. Flash MicroPython Firmware onto Raspberry Pi Pico
	- **Download MicroPython Firmware**: Visit the [MicroPython download page](https://micropython.org/download/rp2-pico/) and download the latest `.uf2` file for the Raspberry Pi Pico.
	- **Connect Pico to Computer**: Hold down the `BOOTSEL` button on your Pico and connect it to your computer using the micro USB cable. Release the `BOOTSEL` button once connected.
	- **Flash Firmware**: Your Pico will appear as a USB mass storage device. Drag and drop the `.uf2` file onto the Pico’s drive. It will reboot automatically and will now run MicroPython.
4. Find Your Pico’s Serial Port
	- On Windows, it might appear as a COM port (e.g., COM3). You can find this in Device Manager under “Ports (COM & LPT)”.
```bash
ls /dev/tty.* #on Linux
ls /dev/cu.usbmodem* #on MacOS
```
5. Run the following Python script:
```Python
import os
import subprocess

def create_directory(port, directory):
    """Create a directory on the board if it does not exist."""
    ampy_path = '/home/screedy/.local/bin/ampy'  # Full path to ampy
    try:
        subprocess.run([ampy_path, '--port', port, 'mkdir', directory], check=True)
    except subprocess.CalledProcessError as e:
        # Ignore error if directory already exists
        if "EEXIST" not in str(e):
            print(f"Error creating directory {directory}: {e}")

def upload_directory(directory, port):
    ampy_path = '/home/screedy/.local/bin/ampy'  # Full path to ampy
    for root, dirs, files in os.walk(directory):
        for dir in dirs:
            # Create corresponding directory structure on the board
            remote_dir = os.path.join(root, dir).replace(directory, '').replace('\\', '/')
            if remote_dir.startswith('/'):
                remote_dir = remote_dir[1:]
            print(f"Creating directory {remote_dir}")
            create_directory(port, remote_dir)

        for file in files:
            local_path = os.path.join(root, file)
            remote_path = local_path.replace(directory, '').replace('\\', '/')
            if remote_path.startswith('/'):
                remote_path = remote_path[1:]
            print(f"Uploading {local_path} to {remote_path}")
            try:
                subprocess.run([ampy_path, '--port', port, 'put', local_path, remote_path], check=True)
            except subprocess.CalledProcessError as e:
                print(f"Error uploading {local_path}: {e}")

if __name__ == "__main__":
    directory = input("Enter the directory to upload: ")
    port = input("Enter the serial port (e.g., /dev/ttyUSB0 or COM3): ")
    upload_directory(directory, port)
```

6. Open Thonny IDE, connect to the Raspberry Pi Pico, load the main.py file from the RP2040 and click run.

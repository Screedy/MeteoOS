
# MeteoOS C++ Source Code Documentation
- This documentation outlines the procedures for working with the [MeteoOS](https://github.com/Screedy/MeteoOS.git) source code contained within the pico-boilerplate directory.

## Prebuild Firmware
- For quick deployment, you can directly load the prebuilt `MeteoOS.uf2` file onto your Raspberry Pi Pico. This file contains the current version of the firmware.

## Building Your Own Version
- If you prefer to compile your own version of [MeteoOS](https://github.com/Screedy/MeteoOS.git), follow the detailed steps below for MacOS and Linux systems.

### Setup on MacOS/Linux
1. **Install Development Tools:**
	- Install CMake, the GCC cross-compiler, and essential build tools:
```BASH
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib build-essential
```
2. **Clone the MeteoOS Repository:**
	- Retrieve the latest version of the [MeteoOS](https://github.com/Screedy/MeteoOS.git) source code:
```BASH
git clone https://github.com/Screedy/MeteoOS.git
```
3. **Setup the [Pico SDK](https://github.com/raspberrypi/pico-sdk):**
	- Obtain the SDK and initialize required submodules:
```BASH
cd MeteoOS/C++
git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
export PICO_SDK_PATH=`pwd`
cd ../
```
4. **Clone [Pimoroni Pico](https://github.com/pimoroni/pimoroni-pico) Libraries:**
	- These libraries are utilized for various hardware functionalities such as the display:
```BASH
git clone https://github.com/pimoroni/pimoroni-pico
```
5. **Clone the [no-OS-FatFS-SD-SPI-RPi-Pico](https://github.com/carlk3/no-OS-FatFS-SD-SPI-RPi-Pico) Library:**
	- This library is necessary for SD card functionalities:
```BASH
mkdir pico-boilerplate/lib
cd pico-boilerplate/lib
git clone https://github.com/carlk3/no-OS-FatFS-SD-SPI-RPi-Pico.git
```

#### Building the Application
1. **Prepare the Build Environment:**
	- Create and navigate to the build directory:
```BASH
pwd  # Ensure you are in the /{your_path}/MeteoOS/C++ directory
mkdir build && cd build
cmake ../pico-boilerplate/
```
2. **Compile the Project:**
	- Start the compilation process:
```BASH
make
```

### Windows
TBD

---

### Deploying the build to the Raspberry Pi Pico

#### Quick Deployment
- To quickly load the final version of your application onto the Raspberry Pi Pico:

1. **BOOTSEL Mode:**
	- Press and hold the `BOOTSEL` button while plugging the Pico to your computer via USB.
	- Release the button once connected. The Pico will mount as a mass storage device named `RPI-RP2`.
	- Drag and drop your `MeteoOS.uf2` file onto the `RPI-RP2` drive.

#### Automated Deployment
- For a more seamless experience that doesn’t require manually entering `BOOTSEL` mode after every change and needing to unplug and plug your device back again:

**On Linux/MacOS:**
1. **Install Dependencies and Clone picotool:**
	- Install required packages and clone the [picotool](https://github.com/raspberrypi/picotool) repository into your project directory:
```BASH
pwd
# > /{your_path}/MeteoOS/C++ <--- You should be here
```
```BASH
sudo apt install build-essential pkg-config libusb-1.0-0-dev cmake
git clone https://github.com/raspberrypi/picotool.git
```
2. **Build picotool:**
	- Navigate into the cloned directory, set up the build environment, and compile picotool:
```BASH
cd picotool
mkdir build && cd build
export PICO_SDK_PATH=../../pico-sdk # Adjust this path to where your pico-sdk resides.
cmake ..
make
```
3. **Verify picotool Installation:**
	- Ensure picotool is correctly built and operational:
```BASH
./picotool help # Outputs help information.
```
4. **Prepare the Project:**
	- Ensure `pico_enable_stdio_usb(${NAME} 1)` is active in `C++/pico-boilerplate/CMakeLists.txt` to **enable USB output**, **enabled by default**.
5. **Rebuild Your Project:**
	- Rebuild your project to update the `MeteoOS.uf2` file.
6. **Load the Application:**
	- Use picotool to automatically upload the UF2 file to the Pico:
```BASH
../picotool/build/picotool load -f MeteoOS.uf2
```

---

### Debugging the App
- For real-time debugging and output monitoring:

- **Using the screen Command:**
	- Open a terminal session connected to your Pico using `screen`. Adjust the USB port path as necessary for your setup:
```BASH
screen /dev/cu.usbmodem11101 115200
```
- The port `/dev/cu.usbmodem11101` is an example; replace it with the actual port connected to your Pico.
- The baud rate `115200` is fixed and **should not** be modified.

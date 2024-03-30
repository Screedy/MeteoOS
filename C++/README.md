# C++ version

- This folder contains all of the source code for MeteoOS in the pico-boilerplate folder.

- It is possible, to just load the prebuild file MeteoOS.uf2 to your pico. It contains the current stable version.

## Building your own version
- If you insist on building your own version you will need to follow these instructions:

### MacOS/Linux
First you need to install the Pico SDK and other dependencies:
1. Install CMake ,GCC cross compiler and build-essential:
```BASH
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib build-essential
```
2. Clone the [MeteoOS](https://github.com/Screedy/MeteoOS.git) repository:
```BASH
git clone https://github.com/Screedy/MeteoOS.git
```
4.  Clone the SDK locally:
```BASH
cd MeteoOS/C++
git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
export PICO_SDK_PATH=`pwd`
cd ../
```
3. Grab the [Pimoroni Pico libraries](https://github.com/pimoroni/pimoroni-pico):
	- They should be in the C++ folder.
```BASH
git clone https://github.com/pimoroni/pimoroni-pico
```

#### Building the application
First you need to navigate into the boilerplate (assuming you are in the C++ directory):
```BASH
cd pico-boilerplate
```

Make sure that the `CMakeLists.txt` is setup correctly with all source files and libraries you want (by default all used libraries and files needed for this project are included)

Than run the CMake:
```BASH
cmake ..
```

Now we can go back to the C++ folder and build the application:
```BASH
cd ..
make
```

### Windows
TBD

### Getting the build onto the RP Pico
#### The-easy-method
To get your program onto the RP Pico there are two easy ways to do it. If you just want to get the final version of the program onto your device, the easiest way to do this is to hold the `BOOTSEL` button while plugging your device onto your computer. Than just simple drag your `MeteoOS.uf2` onto the drive called RPI-RP2

#### The better method
If you don't want to be unplugging your device every time you change something in the build you can follow these steps to automatically force your Pico into bootsel mode and loading the build automatically:
##### Linux/MacOS
1. Clone the [picotool](https://github.com/raspberrypi/picotool) library. Destination is up to you but assuming it is in the C++ folder:
```BASH
sudo apt install build-essential pkg-config libusb-1.0-0-dev cmake
git clone https://github.com/raspberrypi/picotool.git
```
2. Build the [picotool](https://github.com/raspberrypi/picotool):
```BASH
mkdir build
cd build
export PICO_SDK_PATH=../../pico-sdk #Make sure to change this to your pico-sdk library.
cmake ..
make
```
3. Once the build has finished you should have the picotool binary in your build directory. You can verify if it works like this:
```BASH
./picotool help #This will print the help page.
```
4. Make sure that the `CMakeLists.txt` file in pico-boilerplate has the `pico_enable_stdio_usb(${NAME} 1)` uncommented. This should be done by default.
5. Now you need to build the project again. After the build is done you will have the `MeteoOS.uf2` file in the directory. Now you need to use the [easy method](#The-easy-method) one more time.
6. Now you can load your build like this:
```BASH
picotool/build/picotool load -f MeteoOS.uf2
```
cmake_minimum_required(VERSION 3.12)

# Project name
set(NAME MeteoOS)

# Set the pico_sdk path
# !IMPORTANT If your path to pico-sdk is different either change it here 
# or if you have PICO_SDK_PATH setup in Shell Environment you can comment this line.
set(PICO_SDK_PATH "../pico-sdk")

include(pico_sdk_import.cmake)
include(pimoroni_pico_import.cmake)

# Gooey boilerplate
project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Set compile options for both C and C++ files
add_compile_options(-fexceptions)

# Enable exceptions on the Pico itself
set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# Initialize the SDK
pico_sdk_init()

# Option for test build
option(TEST_BUILD "Build for testing" ON)
if(TEST_BUILD)
    add_compile_definitions(TEST_BUILD)
endif()


# Tell CMake where to find the executable source file
add_executable(${NAME}
    	main.cpp
    	config/config.cpp
    	config/config.h
    	config/Display.cpp
    	config/Display.h
	config/rtc_module.h
	config/rtc_module.cpp
    	graphics/graphics.cpp
    	graphics/graphics.h
    	graphics/page_elements.cpp
    	graphics/page_elements.h
	graphics/qrcode_graphics.h
	graphics/qrcode_graphics.cpp
	graphics/graph/concrete_strategy_daily.h
	graphics/graph/concrete_strategy_daily.cpp
	graphics/graph/concrete_strategy_weekly.h
	graphics/graph/concrete_strategy_weekly.cpp
	graphics/graph/context_graph_interval.h
	graphics/graph/context_graph_interval.cpp
	graphics/graph/strategy_graph_interval.h
	graphics/graph/strategy_graph_interval.cpp
    	sensors/DHT11.h
    	sensors/DHT11.cpp
	sensors/Sensor.h
	sensors/Sensor.cpp
	sensors/SensorManager.cpp
	sensors/SensorManager.h
	pages/Settings.h
	pages/Settings.cpp
	pages/add_sensor.h
	pages/add_sensor.cpp
	pages/brightness.h
	pages/brightness.cpp
	pages/del_data.h
	pages/del_data.cpp
	pages/del_sensor.h
	pages/del_sensor.cpp
	pages/format_sd.h
	pages/format_sd.cpp
	pages/set_time.h
	pages/set_time.cpp
	#config/sd_card_config.h
	config/hw_config.cpp
	config/sd_card_manager.h
	config/sd_card_manager.cpp
	config/startup.h
	config/startup.cpp
	config/setup.h
	config/setup.cpp
	lib/QR-Code-generator/qrcodegen.hpp
	lib/QR-Code-generator/qrcodegen.cpp
)

# Tell CMake where to find other source code
add_subdirectory(lib/no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI)

# Include required libraries
# This assumes `pimoroni-pico` is stored alongside your project
include(common/pimoroni_i2c)
include(common/pimoroni_bus)
include(libraries/bitmap_fonts/bitmap_fonts)
include(libraries/hershey_fonts/hershey_fonts)
include(libraries/pico_explorer/pico_explorer)
include(libraries/pico_display/pico_display)


# Link the required libraries
target_link_libraries(${NAME}
    pimoroni_i2c
    pico_explorer
    pico_display
    FatFs_SPI
)

# Use USB instead of UART for picotool and screen functionality
pico_enable_stdio_usb(${NAME} 1)
pico_enable_stdio_uart(${NAME} 0)

# Create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})

# Set up files for the release packages
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.uf2
    ${CMAKE_CURRENT_LIST_DIR}/README.md
    DESTINATION .
)

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)

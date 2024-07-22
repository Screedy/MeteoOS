cmake_minimum_required(VERSION 3.6)

# Project name
set(NAME MeteoOS)

# Set the pico_sdk path
# !IMPORTANT If your path to pico-sdk is different either change it here 
# or if you have PICO_SDK_PATH setup in Shell Environment you can comment this line.
set(PICO_SDK_PATH "../pico-sdk")

include(pico_sdk_import.cmake)
include(pimoroni_pico_import.cmake)

project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Set compile options for both C and C++ files
add_compile_options(-fexceptions)
set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# Initialize the SDK
pico_sdk_init()

# Options for test builds
option(TEST_BUILD "Build for testing" OFF) # Default to OFF
if(TEST_BUILD)
    add_compile_definitions(TEST_BUILD)
endif()

option(DRAW_QR_CODE_TEST "Enable QR Code Drawing Test" OFF) # Default to OFF
if(DRAW_QR_CODE_TEST)
    add_compile_definitions(DRAW_QR_CODE_TEST)
endif()

option(RENDER_QR_CODE_TEST "Enable QR Code Rendering Test" OFF) # Default to OFF
if(RENDER_QR_CODE_TEST)
    add_compile_definitions(RENDER_QR_CODE_TEST)
endif()

option(STORAGE_TEST "Tests Both Success and Failed SD Card Access" OFF) # Default to OFF
if(STORAGE_TEST)
    add_compile_definitions(STORAGE_TEST)
endif()

option(LIST_DIR_TEST "Times the listing of everything in root dir" OFF) # Default to OFF
if(LIST_DIR_TEST)
    add_compile_definitions(LIST_DIR_TEST)
endif()

option(TEST_HOMEPAGE_RENDER "Time in second how long it takes to render the homepage" OFF) # Default to OFF
if(TEST_HOMEPAGE_RENDER)
    add_compile_definitions(TEST_HOMEPAGE_RENDER)
endif()

option(TEST_MEMORY_HOMEPAGE "Tests the memory free on the device" OFF) # Default to OFF
if(TEST_MEMORY_HOMEPAGE)
    add_compile_definitions(TEST_MEMORY_HOMEPAGE)
endif()

option(TEST_GRAPH_SPEED "Tests the speed of generating a graph" OFF) # Default to OFF
if(TEST_GRAPH_SPEED)
    add_compile_definitions(TEST_GRAPH_SPEED)
endif()

option(TEST_GRAPH_MEMORY "Tests the memory of generating a graph" OFF) # Default to OFF
if(TEST_GRAPH_MEMORY)
    add_compile_definitions(TEST_GRAPH_MEMORY)
endif()

# Definition of source and header files using globbing
file(GLOB CONFIG_SOURCES "config/*.cpp" "config/*.h")
file(GLOB GRAPHICS_SOURCES "graphics/*.cpp" "graphics/*.h")
file(GLOB GRAPH_SOURCES "graphics/graph/*.cpp" "graphics/graph/*.h")
file(GLOB SENSORS_SOURCES "sensors/*.cpp" "sensors/*.h")
file(GLOB PAGES_SOURCES "pages/*.cpp" "pages/*.h")
file(GLOB UTILS_SOURCES "utils/*.cpp" "utils/*.h")

# Tell CMake where to find the executable source file
add_executable(${NAME}
    	main.cpp
	${CONFIG_SOURCES}
	${GRAPHICS_SOURCES}
	${GRAPH_SOURCES}
	${SENSORS_SOURCES}
	${PAGES_SOURCES}
	${UTILS_SOURCES}
	lib/QR-Code-generator/qrcodegen.hpp
	lib/QR-Code-generator/qrcodegen.cpp
	pages/reset_graph.h
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

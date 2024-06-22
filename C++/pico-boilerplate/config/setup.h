//
// Created by Petr Jurásek on 21.06.2024.
//

#ifndef PICO_BOILERPLATE_SETUP_H
#define PICO_BOILERPLATE_SETUP_H

#include <functional>

#include "Display.h"
#include "sd_card_manager.h"
#include "config.h"

/*
 * Starts the wizard for the first time configuration of the device.
 */
void wizard_start();

/*
 * Sets up the pins for first thermal sensor.
 * Returns -1 if the sensor is not defined. Else returns the pin number.
 */
int pin_setup();

/*
 * Sets up the pins for the SD card adapter.
 */
void sd_card_setup();

/*
 * Interrupts the current function and displays the help screen.
 */
void help_interrupt();

/*
 * Initiates the first time setup. This function is called when the settings.txt file is not found.
 * Guides the user through the setup process and connects first thermal sensor and SD card.
 */
void initial();

/*
 * Waits for the Y button to be pressed and then returns to the parent function.
 * If the X button is pressed, the help screen is displayed with QR code to the GitHub repository.
 */
void wait_for_y(std::function<void()> func);

/*
 * Clears the pin number on the screen.
 */
void clear_pin();

/*
 * Sets the default values for the settings.txt file.
 */
void set_defaults();

#endif //PICO_BOILERPLATE_SETUP_H

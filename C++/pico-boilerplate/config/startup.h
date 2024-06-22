//
// Created by Petr Jurásek on 21.06.2024.
//

#ifndef PICO_BOILERPLATE_STARTUP_H
#define PICO_BOILERPLATE_STARTUP_H

#include "setup.h"

/*
 * Function that is called at the beginning of the RP Pico.
 * It should:
 *  - Start the wizard to configure the device on first boot.
 *  - Initialize the SD card.
 *  - Initialize the Display and it's singleton.
 *  - Initialize the Sensor manager and it's singleton.
 */
void startup();


#endif //PICO_BOILERPLATE_STARTUP_H

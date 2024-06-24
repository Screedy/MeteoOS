//
// Created by Petr Jurásek on 24.06.2024.
//

#ifndef PICO_BOILERPLATE_DEL_SENSOR_H
#define PICO_BOILERPLATE_DEL_SENSOR_H

#include <string>
#include "../config/config.h"
#include "../graphics/graphics.h"
#include "../sensors/Sensor.h"
#include "../sensors/SensorManager.h"

/*
 * Renders the function to delete a sensor. Generates a form where the user can select the sensor to delete.
 *
 * @return True if the sensor was deleted, false if the user canceled the operation.
 */
bool render_del_sensor();

/*
 * Selects the sensor you want to delete.
 *
 * @return The index of the sensor.
 */
int select_sensor();

#endif //PICO_BOILERPLATE_DEL_SENSOR_H

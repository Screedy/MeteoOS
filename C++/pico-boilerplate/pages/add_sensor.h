//
// Created by Petr Jurásek on 08.04.2024.
//

#ifndef PICO_BOILERPLATE_ADD_SENSOR_H
#define PICO_BOILERPLATE_ADD_SENSOR_H

#include <string>
#include "../config/config.h"
#include "../graphics/graphics.h"
#include "../sensors/Sensor.h"
#include "../sensors/SensorManager.h"

namespace AddSensor{
    extern Display& display;
    extern pimoroni::ST7789& driver;
    extern pimoroni::PicoGraphics_PenRGB332& graphics;
    extern Buttons& buttons;
    extern SensorManager& sensor_manager;
}

/*
 * Renders the function to add a new sensor. Generates a form where the user can select the sensor type,
 * pin, name and interval.
 *
 * @return True if the sensor was added, false if the user canceled the operation.
 */
bool render_add_sensor();

/*
 * Selects the sensor type you want to add.
 * Possible sensor types are:
 * - DHT11
 *
 * @return The type of the sensor.
 */
SensorType select_sensor_type();

/*
 * Selects the pin where the sensor is connected.
 *
 * @return Pin selected by user.
 */
int select_sensor_pin();

/*
 * Selects the name of the sensor.
 *
 * @return Name of the sensor.
 */
std::string select_sensor_name();

/*
 * Selects the interval of the sensor.
 *
 * @return The number of seconds between sensor readings.
 */
int select_interval();

#endif //PICO_BOILERPLATE_ADD_SENSOR_H

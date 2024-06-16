//
// Created by Petr Jurásek on 30.03.2024.
//

#ifndef PICO_BOILERPLATE_SENSOR_H
#define PICO_BOILERPLATE_SENSOR_H

#include <string>
#include "SensorType.h"

/*
 * An abstract class that represents a generic sensor.
 * Includes all the common functions that a sensor needs to implement.
 *
 * @function read() - reads the data from the sensor.
 * @function getTemperature() - returns the temperature read from the sensor.
 * @function getHumidity() - returns the humidity read from the sensor.
 * @function getName() - returns the name of the sensor.
 * @function getType() - returns the type of the sensor.
 * @function getPin() - returns the GPIO pin the sensor is connected to.
 *
 */
class Sensor {
public:
    virtual ~Sensor() {}
    int virtual read() = 0;
    float virtual getHumidity() = 0;
    float virtual getTemperature() = 0;
    std::string virtual getName() = 0;
    SensorType virtual getType() = 0;
    int virtual getPin() = 0;
};

std::string sensor_type_to_string(SensorType type);


#endif //PICO_BOILERPLATE_SENSOR_H

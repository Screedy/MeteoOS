//
// Created by Petr Jurásek on 30.03.2024.
//

#ifndef PICO_BOILERPLATE_SENSOR_H
#define PICO_BOILERPLATE_SENSOR_H

#include <string>
#include "SensorType.h"
#include "pico/stdlib.h"
#include "hardware/timer.h"

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
    /*
     * Destructor of the Sensor class.
     */
    virtual ~Sensor() {}

    /*
     * Reads the data from the sensor.
     *
     * @return Error code.
     * 0 - Success.
     * 1 - Sensor did not respond.
     * 2 - Checksum error.
     */
    int virtual read() = 0;
    float virtual getHumidity() = 0;
    float virtual getTemperature() = 0;
    std::string virtual getName() = 0;
    SensorType virtual getType() = 0;
    int virtual getPin() = 0;
    virtual char* getSensorType() = 0;
    virtual int getInterval() = 0;
    virtual bool handle_timer();

private:
    repeating_timer_t timer;
};


std::string sensor_type_to_string(SensorType type);


#endif //PICO_BOILERPLATE_SENSOR_H

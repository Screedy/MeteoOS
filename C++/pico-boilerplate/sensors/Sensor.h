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

    /*
     * Returns the humidity and temperature read from the sensor.
     */
    float virtual getHumidity() = 0;

    /*
     * Returns the temperature read from the sensor.
     */
    float virtual getTemperature() = 0;

    /*
     * Returns the name of the sensor.
     */
    std::string virtual getName() = 0;

    /*
     * Returns the type of the sensor.
     */
    SensorType virtual getType() = 0;

    /*
     * Returns the GPIO pin the sensor is connected to.
     */
    int virtual getPin() = 0;

    /*
     * Returns the sensor type as a string.
     */
    virtual char* getSensorType() = 0;

    /*
     * Returns the sensor interval.
     */
    virtual int getInterval() = 0;

    /*
     * Handles the timer interrupt.
     */
    virtual bool handle_timer();

private:
    repeating_timer_t timer;
};

/*
 * Converts the SensorType enum to a string.
 *
 * @param type - SensorType enum.
 * @return SensorType as a string.
 */
std::string sensor_type_to_string(SensorType type);


#endif //PICO_BOILERPLATE_SENSOR_H

//
// Created by Petr Jurásek on 16.06.2024.
//

#ifndef PICO_BOILERPLATE_SENSORTYPE_H
#define PICO_BOILERPLATE_SENSORTYPE_H

/*
 * An enum that represents all the sensor types supported by the MeteoOS.
 *
 * DHT11 - A sensor that measures temperature and humidity.
 * DS18B20 - A sensor that measures temperature.
 * UNKNOWN - A sensor that is not supported.
 */
enum class SensorType {
    DHT11,    // Assume 0
    DS18B20,   // Assume 1
    UNKNOWN   // Assume last
};

#endif //PICO_BOILERPLATE_SENSORTYPE_H

//
// Created by Petr Jurásek on 30.03.2024.
//

#ifndef PICO_BOILERPLATE_SENSOR_H
#define PICO_BOILERPLATE_SENSOR_H

#include <string>

class Sensor {
public:
    virtual ~Sensor() {}
    int virtual read() = 0;
    float virtual getHumidity() = 0;
    float virtual getTemperature() = 0;
    std::string virtual getName() = 0;
};

enum class SensorType {
    DHT11,
    UNKNOWN
};

std::string sensor_type_to_string(SensorType type);


#endif //PICO_BOILERPLATE_SENSOR_H

//
// Created by Petr Jurásek on 30.03.2024.
//

#ifndef PICO_BOILERPLATE_SENSOR_H
#define PICO_BOILERPLATE_SENSOR_H

class Sensor {
public:
    virtual ~Sensor() {}
    int virtual read() = 0;
    float virtual getHumidity() = 0;
    float virtual getTemperature() = 0;
};

#endif //PICO_BOILERPLATE_SENSOR_H

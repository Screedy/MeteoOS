//
// Created by Petr Jurásek on 19.03.2024.
//

#ifndef PICO_BOILERPLATE_DHT11_H
#define PICO_BOILERPLATE_DHT11_H

#include <chrono>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include <cstring>
#include <string>
#include "Sensor.h"

/*
 * The DHT11 class is responsible for reading the temperature and humidity from the DHT11 sensor.
 * It creates a new instance of the sensor and reads the data from it.
 *
 * The sensor is read every interval seconds and the data is stored in the temperature and humidity fields.
 *
 * @param pin - the GPIO pin the sensor is connected to.
 * @param name - the name of the sensor.
 * @param interval - the interval in seconds at which the sensor is read. If the interval is less than 0,
 * the sensor won't be read automatically and the read() function has to be called manually.
 *
 * @function read() - reads the data from the sensor and stores it in the temperature and humidity fields.
 * @function getTemperature() - returns the temperature read from the sensor.
 * @function getHumidity() - returns the humidity read from the sensor.
 * @function getName() - returns the name of the sensor. Example "PC".
 * @function getType() - returns the type of the sensor. In this case, it returns SensorType::DHT11.
 * @function getPin() - returns the GPIO pin the sensor is connected to. Example 1.
 *
 */
class DHT11 : public Sensor {
private:
    unsigned int pin;
    std::string name;
    int interval;
    float temperature;
    float humidity;
    bool write;
    char* sensorType;
    repeating_timer_t timer;


    void write_to_file();
    bool waitForChange(bool state, unsigned int timeout_us);
    std::uint8_t readByte();

public:
    DHT11(unsigned int pin, std::string name, int interval);
    int read();
    float getTemperature();
    float getHumidity();
    std::string getName();
    SensorType getType();
    int getPin();
    char* getSensorType();
    int getInterval();
    bool handle_timer();
};

static bool timer_callback_dht(repeating_timer_t *rt);

#endif //PICO_BOILERPLATE_DHT11_H

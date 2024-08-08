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
    std::chrono::high_resolution_clock::time_point last_read;

    /*
     * Writes the data to a designated file for this sensor on the SD card.
     * The data is written in the following format:
     * (yyyy, mm, dd, dotw, hh, mm, ss);temperature;humidity
     */
    void write_to_file();

    /*
     * Waits for the pin to change its state.
     * This function is used to wait for the sensor to send the data. Uses busy waiting.
     */
    bool waitForChange(bool state, unsigned int timeout_us);

    /*
     * Reads a single byte from the sensor.
     * The byte is read by reading 8 bits from the sensor.
     */
    std::uint8_t readByte();

public:
    /*
     * Creates a new instance of the DHT11 sensor.
     * The sensor is read every interval seconds and the data is stored in the temperature and humidity fields.
     *
     * @param pin - the GPIO pin the sensor is connected to.
     * @param name - the name of the sensor.
     * @param interval - the interval in seconds at which the sensor is read. If the interval is less than 0,
     */
    DHT11(unsigned int pin, std::string name, int interval);

    /*
     * Reads the data from the sensor.
     * The data is read from the sensor and stored in the temperature and humidity fields.
     *
     * @return 0 if the data was read successfully, -1 if an error occurred.
     */
    int read();

    /*
     * Returns the temperature read from the sensor.
     *
     * @return the temperature read from the sensor.
     */
    float getTemperature();

    /*
     * Returns the humidity read from the sensor.
     *
     * @return the humidity read from the sensor.
     */
    float getHumidity();

    /*
     * Returns the name of the sensor.
     *
     * @return the name of the sensor.
     */
    std::string getName();

    /*
     * Returns the type of the sensor.
     *
     * @return the type of the sensor. This is always DHT11.
     */
    SensorType getType();

    /*
     * Returns the GPIO pin the sensor is connected to.
     *
     * @return the GPIO pin the sensor is connected to.
     */
    int getPin();

    /*
     * Returns the sensor type.
     *
     * @return the sensor type.
     */
    char* getSensorType();

    /*
     * Returns the interval at which the sensor is read.
     *
     * @return the interval at which the sensor is read.
     */
    int getInterval();

    /*
     * Handles the timer interrupt.
     *
     * @return true if the timer interrupt was handled, false otherwise.
     */
    bool handle_timer();

    void setWrite(bool write);

    bool getWrite();
};

/*
 * The timer callback function for the DHT11 sensor.
 * This function is called every interval seconds and reads the data from the sensor.
 *
 * @param rt - the repeating timer structure.
 *
 * @return true if the timer callback was successful, false otherwise.
 */
static bool timer_callback_dht(repeating_timer_t *rt);

#endif //PICO_BOILERPLATE_DHT11_H

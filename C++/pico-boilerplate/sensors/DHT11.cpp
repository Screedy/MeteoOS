//
// Created by Petr Jurásek on 19.03.2024.
//

#include "DHT11.h"

DHT11::DHT11(unsigned int pin, std::string name, int interval)
    : pin(pin), interval(interval), temperature(0), humidity(0) {

    const char* sensorType = "DHT11";
    this->sensorType = new char[strlen(sensorType) + 1];
    strcpy(this->sensorType, sensorType);

    gpio_init(this->pin);

    //Copy first 6 characters of the name and add null terminator
    this->name = name.substr(0, 6);
    this->name += '\0';

    if (interval < 0) {
        this->write = true;
    } else {
        this->write = false;
    }
}

std::uint8_t DHT11::readByte() {
    std::uint8_t result = 0;
    for (int i = 7; i >= 0; i--){
        waitForChange(1, 50);
        sleep_us(30);
        if (gpio_get(this->pin) == 1){
            result |= (1 << i);
            waitForChange(0, 50);
        }
    }
    return result;
}

int DHT11::read() {

    // Send start signal
    gpio_set_dir(this->pin, GPIO_OUT);
    gpio_put(this->pin, 0);
    sleep_ms(20);
    gpio_put(this->pin, 1);
    gpio_set_dir(this->pin, GPIO_IN);
    gpio_pull_up(this->pin);

    // Wait for the sensor to respond
    if (!waitForChange(0, 40)) return -1;
    if (!waitForChange(1, 90)) return -1;
    if (!waitForChange(0, 90)) return -1;

    // Read the data
    std::uint8_t humI = readByte();
    std::uint8_t humF = readByte();
    std::uint8_t tempI = readByte();
    std::uint8_t tempF = readByte();
    std::uint8_t checksum = readByte();

    // Check the checksum
    if (checksum != (humI + humF + tempI + tempF)) return -1;

    // Store the data
    this->humidity = humI + (humF / 100.0F);
    this->temperature = tempI + (tempF / 100.0F);

    return 0;
}

bool DHT11::waitForChange(bool state, unsigned int timeout_us){
    auto start = time_us_32();
    while (gpio_get(this->pin) != state) {
        if (time_us_32() - start > timeout_us) return false;
        tight_loop_contents();
    }
    return true;
}

float DHT11::getTemperature() {
    return this->temperature;
}

float DHT11::getHumidity() {
    return this->humidity;
}

std::string DHT11::getName() {
    return this->name;
}

SensorType DHT11::getType() {
    return SensorType::DHT11;
}

int DHT11::getPin() {
    return this->pin;
}

char* DHT11::getSensorType() {
    return this->sensorType;
}

int DHT11::getInterval() {
    return this->interval;
}
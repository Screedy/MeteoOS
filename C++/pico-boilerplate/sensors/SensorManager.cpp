//
// Created by Petr Jurásek on 30.03.2024.
//
#include <string>
#include <vector>
#include <sstream>

#include "SensorManager.h"
#include "../config/sd_card_manager.h"
#include "../config/config.h"

SensorManager::SensorManager()
: activeSensor(0) {
    //Load sensors from file
    loadSensors();

    // Get available pins, remove the ones that are already in use
    avPins = getAvailablePins();

    // Add a DHT11 sensor for testing
    //sensors.push_back(std::make_unique<DHT11>(DHT11(0, "TEST", 30))); // This is temporary to test the DHT11 sensor

    reloadSensorCount();

}

SensorManager& SensorManager::getInstance() {
    static SensorManager instance;
    return instance;
}

std::vector<std::unique_ptr<Sensor>>& SensorManager::getSensors() {
    return sensors;
}

std::unique_ptr<Sensor>& SensorManager::getSensor(int index) {
    return sensors[index];
}

void SensorManager::addSensor(std::unique_ptr<Sensor> sensor) {
    sd_card_manager* sd_card_manager = sd_card_manager::get_instance();
    FIL fil = sd_card_manager->get_fil();
    FRESULT fr;

    const char* path = "0:/config/sensors.txt";

    //append to 0:/config/sensors.txt
    //format: sensorPin;sensorType;sensorName;sensorInterval
    fr = f_open(&fil, path, FA_WRITE | FA_OPEN_APPEND | FA_CREATE_ALWAYS);
    if(fr != FR_OK){
        printf("Failed to open file %s\n", path);
    }

    std::string sensorStr =
            std::to_string(sensor->getPin()) + ";" +
            sensor->getSensorType() + ";" +
            sensor->getName() + ";" +
            std::to_string(sensor->getInterval()) + "\n";

    f_puts(sensorStr.c_str(), &fil);
    f_close(&fil);

    //add sensor to vector of sensors.
    sensors.push_back(std::move(sensor));
    reloadSensorCount();
}

void SensorManager::removeSensor(int index) {
    // TODO: needs testing
    sd_card_manager* sd_card_manager = sd_card_manager::get_instance();
    FIL fil = sd_card_manager->get_fil();
    FRESULT fr;

    const char* path = "0:/config/sensors.txt";

    // open the file for reading
    fr = f_open(&fil, path, FA_READ);
    if(fr != FR_OK){
        printf("Failed to open file %s\n", path);
    }

    // read the file line by line and store it in a vector
    std::vector<std::string> lines;
    char buffer[100]; // Enough for the longest line in the file
    while (f_gets(buffer, sizeof(buffer), &fil)) {
        std::string line(buffer);
        lines.push_back(line);
    }
    f_close(&fil);

    // remove the line with the sensor
    lines.erase(lines.begin() + index);

    // open the file for writing
    fr = f_open(&fil, path, FA_WRITE | FA_CREATE_ALWAYS);
    if(fr != FR_OK){
        printf("Failed to open file %s\n", path);
    }

    // write the modified content back to the file
    for (auto& line : lines) {
        f_puts(line.c_str(), &fil);
    }
    f_close(&fil);

    // remove the sensor from the vector
    sensors.erase(sensors.begin() + index);
    reloadSensorCount();
}

void SensorManager::activeUp() {
    activeSensor++;
    if (activeSensor >= sensors.size()) {
        activeSensor = 0;
    }
}

void SensorManager::activeDown() {
    activeSensor--;
    if (activeSensor < 0) {
        activeSensor = sensors.size() - 1;
    }
}

int SensorManager::getActiveSensor() {
    return activeSensor;
}

std::vector<int> SensorManager::getAvailablePins() {
    std::vector<int> pins = availablePins;
    for (auto& sensor : sensors) {
        pins.erase(std::remove(pins.begin(), pins.end(), sensor->getPin()), pins.end());
    }
    return pins;
}

void SensorManager::loadSensors() {
    sd_card_manager* sd_card_manager = sd_card_manager::get_instance();
    FIL fil = sd_card_manager->get_fil();
    FRESULT fr;

    const char* path = "0:/config/sensors.txt";

    fr = f_open(&fil, path, FA_READ);
    if(fr != FR_OK){
        printf("Failed to open file %s\n", path);
        return;
    }

    char buffer[100]; // Enough for the longest line in the file
    while (f_gets(buffer, sizeof(buffer), &fil)) {
        std::string line(buffer);
        std::vector<std::string> parts = SensorManager::split(line, ';');

        int pin = std::stoi(parts[0]);
        std::string sensorType = parts[1];
        std::string name = parts[2];

        //try setting interval, if it fails set it to 0
        int interval; // NOTE: This is temporary while changing the save file format
        try {
            interval = std::stoi(parts[3]);
        } catch (std::invalid_argument& e) {
            interval = 0;
        }

        #ifdef TEST_BUILD
            printf("Loaded sensor: %d, %s, %s, %d\n", pin, sensorType.c_str(), name.c_str(), interval);
        #endif

        if (sensorType == "DHT11") {
            sensors.push_back(std::make_unique<DHT11>(DHT11(pin, name, interval)));
        } else if (sensorType == "DS18B20") {
            //sensors.push_back(std::make_unique<DS18B20>(DS18B20(pin, name, interval)));
        }
    }
    f_close(&fil);
    reloadSensorCount();
}

std::vector<std::string> SensorManager::split(const std::string& str, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        parts.push_back(item);
    }

    return parts;
}

int SensorManager::getSensorCount() {
    return sensorCount;
}

void SensorManager::reloadSensorCount() {
    sensorCount = sensors.size();
}

void SensorManager::setDefault(){
    sensors.clear();
    //sensors.push_back(std::make_unique<DHT11>(DHT11(0, "TEST", 30))); // This is temporary to test the DHT11 sensor
    reloadSensorCount();
}
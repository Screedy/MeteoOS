//
// Created by Petr Jurásek on 30.03.2024.
//

#include "SensorManager.h"
#include "../config/sd_card_manager.h"

SensorManager::SensorManager()
: activeSensor(0), sensorCount(0) { //TODO: Implement the sensorCount when file for adding sensor is implemented
    sensors.push_back(std::make_unique<DHT11>(DHT11(0, "TEST", 30))); // TODO: This is temporary to test the DHT11 sensor

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
    //TODO: Implement adding sensor to file -- DONE, needs testing
    sd_card_manager* sd_card_manager = sd_card_manager::get_instance();
    FIL fil = sd_card_manager->get_fil();
    FRESULT fr;

    const char* path = "0:/config/sensors.txt";

    //append to 0:/config/sensors.txt
    //format: sensorPin;sensorType;sensorName;sensorInterval
    fr = f_open(&fil, path, FA_WRITE | FA_OPEN_APPEND);
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
}

void SensorManager::removeSensor(int index) {
    sensors.erase(sensors.begin() + index);
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
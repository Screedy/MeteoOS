//
// Created by Petr Jurásek on 30.03.2024.
//

#include "SensorManager.h"

SensorManager::SensorManager() {
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
    sensors.push_back(std::move(sensor));
}

void SensorManager::removeSensor(int index) {
    sensors.erase(sensors.begin() + index);
}
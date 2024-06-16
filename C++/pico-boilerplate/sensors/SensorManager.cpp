//
// Created by Petr Jurásek on 30.03.2024.
//

#include "SensorManager.h"

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
    //TODO: Implement adding sensor to file
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
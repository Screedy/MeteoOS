//
// Created by Petr Jurásek on 30.03.2024.
//

#ifndef PICO_BOILERPLATE_SENSORMANAGER_H
#define PICO_BOILERPLATE_SENSORMANAGER_H

#include <iostream>
#include <vector>
#include <memory>

#include "Sensor.h"
#include "DHT11.h"

/*
 * A singleton class that manages all sensors connected to the Pico.
 * It is responsible for adding, removing and getting sensors.
 *
 * @function getInstance() - returns the instance of the SensorManager.
 * @function getSensors() - returns the vector of sensors.
 * @function getSensor(int index) - returns the sensor at the given index.
 * @function addSensor(std::unique_ptr<Sensor> sensor) - adds a sensor to the vector of sensors.
 * @function removeSensor(int index) - removes the sensor at the given index from the vector of sensors.
 */
class SensorManager {
public:
    static SensorManager& getInstance();
    SensorManager(const SensorManager&) = delete;
    SensorManager& operator=(const SensorManager&) = delete;
    std::vector<std::unique_ptr<Sensor>>& getSensors();
    std::unique_ptr<Sensor>& getSensor(int index);
    void addSensor(std::unique_ptr<Sensor> sensor);
    void removeSensor(int index);
private:
    SensorManager();
    std::vector<std::unique_ptr<Sensor>> sensors;
};


#endif //PICO_BOILERPLATE_SENSORMANAGER_H

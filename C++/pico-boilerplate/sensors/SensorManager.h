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
 */
class SensorManager {
public:
    /*
     * A static method that returns the only instance of the SensorManager.
     *
     * @return The instance of the SensorManager.
     */
    static SensorManager& getInstance();

    SensorManager(const SensorManager&) = delete;
    SensorManager& operator=(const SensorManager&) = delete;

    /*
     * Function that returns all sensors.
     *
     * @return A vector of all sensors.
     */
    std::vector<std::unique_ptr<Sensor>>& getSensors();

    /*
     * Function that returns a sensor at a specific index.
     *
     * @param index The index of the sensor.
     * @return The sensor at the index.
     */
    std::unique_ptr<Sensor>& getSensor(int index);

    /*
     * Function that adds a sensor to the SensorManager.
     *
     * @param sensor The sensor to be added.
     * @return None.
     */
    void addSensor(std::unique_ptr<Sensor> sensor);

    /*
     * Function that removes a sensor from the SensorManager and file.
     *
     * @param index The index of the sensor to be removed.
     * @return None.
     */
    void removeSensor(int index);

    /*
     * Function that changes the active sensor to the next one.
     *
     * @return None.
     */
    void activeUp();

    /*
     * Function that changes the active sensor to the previous one.
     *
     * @return None.
     */
    void activeDown();

    /*
     * Function that returns the index of the active sensor.
     *
     * @return The index of the active sensor.
     */
    int getActiveSensor();
private:
    /*
     * Constructor of the SensorManager.
     */
    SensorManager();

    std::vector<std::unique_ptr<Sensor>> sensors;
    int activeSensor;
    int sensorCount;
    int pins[4] = {0, 1, 2, 3};
};


#endif //PICO_BOILERPLATE_SENSORMANAGER_H

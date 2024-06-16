//
// Created by Petr Jurásek on 30.03.2024.
//

#include "Sensor.h"

std::string sensor_type_to_string(SensorType type) {
    switch (type) {
        case SensorType::DHT11: return "DHT11";
        case SensorType::UNKNOWN: return "UNKNOWN";
        default: return "UNKNOWN";
    }
}
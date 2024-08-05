//
// Created by Petr Jurásek on 11.07.2024.
//

#ifndef PICO_BOILERPLATE_RESET_GRAPH_H
#define PICO_BOILERPLATE_RESET_GRAPH_H

#include <string>
#include "../config/config.h"
#include "../config/Buttons.h"
#include "../config/sd_card_manager.h"
#include "../graphics/graphics.h"
#include "../sensors/Sensor.h"
#include "../sensors/SensorManager.h"


/*
 * Renders the function to reset the graph.
 *
 * @return True if the sensor was reset, false if the user canceled the operation.
 */
void render_reset_graph();

#endif //PICO_BOILERPLATE_RESET_GRAPH_H

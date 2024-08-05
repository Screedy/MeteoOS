//
// Created by Petr Jurásek on 04.08.2024.
//

#ifndef PICO_BOILERPLATE_HOMEPAGE_H
#define PICO_BOILERPLATE_HOMEPAGE_H

#include <vector>
#include <cstdio>
#include <malloc.h>

#include "../config/config.h"
#include "../config/Display.h"
#include "../config/sd_card_manager.h"
#include "../config/rtc_module.h"
#include "../config/Buttons.h"
#include "../graphics/graphics.h"
#include "../graphics/page_elements.h"
#include "../graphics/graph/strategy_graph_interval.h"
#include "../graphics/graph/concrete_strategy_daily.h"
#include "../graphics/graph/concrete_strategy_weekly.h"
#include "../graphics/graph/context_graph_interval.h"
#include "../sensors/SensorManager.h"
#include "Settings.h"

/*
 * Renders the homepage of the device.
 *
 * @param graph_interval The interval in seconds between the graphs.
 * @param last_graph_rendered The last time the graph was rendered.
 */
void render_homepage(int graph_interval, datetime_t* last_graph_rendered);

#endif //PICO_BOILERPLATE_HOMEPAGE_H

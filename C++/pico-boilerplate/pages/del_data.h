//
// Created by Petr Jurásek on 26.06.2024.
//

#ifndef PICO_BOILERPLATE_DEL_DATA_H
#define PICO_BOILERPLATE_DEL_DATA_H

#include "../config/Buttons.h"

/*
 * Deletes the data for a specific sensor selected by the user in this function.
 * @param selected_sensor_index Index of the sensor selected by the user.
 *
 * @return true if the data was deleted or no data was found, false if there was an error deleting the data.
 */
//bool del_data(int selected_sensor_index);

/*
 * Renders the page for deleting data for a specific sensor selected by the user in this function.
 *
 * @return None.
 */
void render_del_data();

#endif //PICO_BOILERPLATE_DEL_DATA_H

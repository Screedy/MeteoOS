//
// Created by Petr Jurásek on 19.06.2024.
//

#ifndef PICO_BOILERPLATE_SD_CARD_CONFIG_H
#define PICO_BOILERPLATE_SD_CARD_CONFIG_H

#include "ff.h"
#include "sd_card.h"

size_t sd_get_num();
sd_card_t *sd_get_by_num(size_t num);

size_t spi_get_num();
spi_t *spi_get_by_num(size_t num);

#endif //PICO_BOILERPLATE_SD_CARD_CONFIG_H

//
// Created by Petr Jurásek on 19.06.2024.
//

#include <string.h>

#include "hw_config.h"
#include "ff.h"
#include "diskio.h"

/*
 * A static configuration of SPI peripherals
 */
static spi_t spis[] = {
        {
        .hw_inst = spi1,
        .miso_gpio = 8,
        .mosi_gpio = 11,
        .sck_gpio = 10,
        .baud_rate = 12 * 1000 * 1000
        }
};

/*
 * A static configuration of SD cards in the system
 */
static sd_card_t sd_cards[] = {
        {
            .pcName = "0:",
            .spi = &spis[0],
            .ss_gpio = 9, // CS pin
            .use_card_detect = false,
            .card_detected_true = 1
        }
};

/*
 * Get number of SD cards in configuration
 */
size_t sd_get_num() {
    return count_of(sd_cards);
}

/*
 * Get SD card configuration by number
 * @param num Number of SD card
 * @return Pointer to SD card configuration or nullptr if not found
 */
sd_card_t *sd_get_by_num(size_t num) {
    assert(num <= sd_get_num());
    if (num <= sd_get_num()) {
        return &sd_cards[num];
    } else {
        return nullptr;
    }
}

/*
 * Get number of SPI peripherals in configuration
 */
size_t spi_get_num() {
    return count_of(spis);
}

/*
 * Get SPI peripheral configuration by number
 * @param num Number of SPI peripheral
 * @return Pointer to SPI peripheral configuration or nullptr if not found
 */
spi_t *spi_get_by_num(size_t num) {
    assert(num <= spi_get_num());
    if (num <= spi_get_num()) {
        return &spis[num];
    } else {
        return nullptr;
    }
}
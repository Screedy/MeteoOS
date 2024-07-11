//
// Created by Petr Jurásek on 19.06.2024.
//

#ifndef PICO_BOILERPLATE_SD_CARD_H
#define PICO_BOILERPLATE_SD_CARD_H

#include <string>
#include <vector>

#include "f_util.h"
#include "ff.h"

#include "sd_card.h"
#include "hw_config.h"

/*
 * A singleton class that represents the SD card connected to the system.
 */
class sd_card_manager {
public:
    /*
     * Get the instance of the class.
     *
     * @return The instance of the class.
     */
    static sd_card_manager *get_instance();

    /*
     * Get the result of the last operation.
     *
     * @return The result of the last operation.
     *
     * @see FRESULT
     * @see f_util.h
     */
    FRESULT get_fr();

    /*
     * Get the file that is currently opened.
     *
     * @return The file that is currently opened.
     *
     * @see FIL
     * @see ff.h
     */
    FIL& get_fil();

    /*
     * Check if file exists.
     *
     * @param path The path to the file.
     *
     * @return True if the file exists, false otherwise.
     */
    bool fileExists(const std::string& path);

    /*
     * Read n lines from already opened file.
     *
     * @param file The file to read from. Must be opened in read mode.
     * @param number_of_lines The number of lines to read.
     * @param lines The vector to store the lines in.
     *
     * @return True if the operation was successful, false otherwise.
     */
    bool read_n_lines(FIL& file, int number_of_lines, std::vector<std::string>& lines);

    /*
     * Mounts the SD card to the system.
     *
     * @return True if the operation was successful, false otherwise.
     */
    bool mount_sd_card();

    /*
     * Unmounts the SD card from the system.
     *
     * @return True if the operation was successful, false otherwise.
     */
    bool unmount_sd_card();

    /*
     * Check if the SD card is mounted.
     *
     * @return True if the SD card is mounted, false otherwise.
     */
    bool is_mounted();

    /*
     * Format the SD card. This will erase all data on the SD card.
     * This will also remove all sensors from SensorManager and launch the setup wizard.
     *
     * @return True if the operation was successful, false otherwise.
     */
    bool format();
private:
    /*
     * The SD card connected to the system.
     */
    sd_card_t *pSD;

    /*
     * Value indicating if the SD card is mounted.
     */
    bool mounted;

    /*
     * Constructor.
     */
    sd_card_manager();

    /*
     * Result of the last operation.
     */
    FRESULT fr;

    /*
     * The file that is currently opened.
     */
    FIL fil;
};


#endif //PICO_BOILERPLATE_SD_CARD_H

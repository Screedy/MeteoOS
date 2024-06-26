//
// Created by Petr Jurásek on 26.06.2024.
//

#include "del_data.h"

#include "../config/config.h"
#include "../config/Display.h"
#include "../sensors/SensorManager.h"
#include "../config/sd_card_manager.h"
#include "../graphics/page_elements.h"
/*
bool del_data(int selected_sensor_index){
    SensorManager& sensor_manager = SensorManager::getInstance();
    sd_card_manager& sd_card_manager = sd_card_manager::getInstance();

    // Get the correct sensor from sensor manager
    std::unique_ptr<Sensor>& selected_sensor = sensor_manager.getSensor(selected_sensor_index);

    // Path to the sensor data file
    const char* path = "0:/measurements/" + selected_sensor->getName() + ".txt";

    // Delete the file
    FRESULT fr = f_unlink(path);
    if(fr != FR_OK){
        printf("Failed to delete file %s\n", path);
        return false;
    }

    return true;
}
 */

void render_del_data(){
    Display& display = Display::getInstance();
    pimoroni::ST7789& driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332& graphics = display.getGraphics();

    sd_card_manager& sd_card_manager = sd_card_manager::getInstance();
    SensorManager& sensor_manager = SensorManager::getInstance();

    const char* path = "0:/measurements/"; // Path to the folder with sensor data

    // List all files in the folder
    DIR dir;
    FILINFO fno;
    FRESULT fr = f_opendir(&dir, path);
    if(fr != FR_OK){
        printf("Failed to open directory %s\n", path);
        return;
    }

    // Save the file names to a vector
    std::vector<std::string> files;
    while(true){
        fr = f_readdir(&dir, &fno);
        if(fr != FR_OK || fno.fname[0] == 0){
            break;
        }
        files.push_back(fno.fname);
    }

    // Close the directory
    f_closedir(&dir);

    int file_index = 0;
    int file_count = files.size();

    while(true){
        // Check for button presses
        if (buttons.is_button_a_pressed()){
            file_index = (file_index + 1) % file_count;
        } else if (buttons.is_button_b_pressed()){
            if (file_index == 0){
                file_index = file_count - 1;
            } else {
                file_index--;
            }
        } else if (buttons.is_button_x_pressed()){
            printf("Deleting file %s\n", files[file_index].c_str());

            // Delete the file
            FRESULT fr = f_unlink((path + files[file_index]).c_str());
            if(fr != FR_OK){
                printf("Failed to delete file %s\n", files[file_index].c_str());
            }
            return;
        } else if (buttons.is_button_y_pressed()){
            printf("Cancelled deletion\n");
            return;
        }

        // Clear the screen
        display.set_color(Colors::BLACK);
        display.clear();
        display.set_color(Colors::WHITE);

        render_nav_arrows(110, Colors::WHITE);
        render_items_list(file_index, files);
        driver.update(&graphics);

        sleep_ms(200);
    }

    del_data(selected_sensor);
}
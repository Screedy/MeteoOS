//
// Created by Petr Jurásek on 26.06.2024.
//

#include "del_data.h"

#include "../config/config.h"
#include "../config/Display.h"
#include "../sensors/SensorManager.h"
#include "../config/sd_card_manager.h"
#include "../graphics/page_elements.h"

bool del_data(int selected_sensor_index){
    SensorManager& sensor_manager = SensorManager::getInstance();
    sd_card_manager* sd_card_manager = sd_card_manager::get_instance();

    // Get the correct sensor from sensor manager
    Sensor* selected_sensor = sensor_manager.getSensor(selected_sensor_index);

    // Path to the sensor data file
    std::string path_str = "0:/measurements/" + selected_sensor->getName() + ".txt";
    const char* path = path_str.c_str();

    // Delete the file
    FRESULT fr = f_unlink(path);
    if(fr != FR_OK){
        printf("Failed to delete file %s\n", path);
        return false;
    }

    return true;
}

void render_del_data(){
    Display& display = Display::getInstance();
    pimoroni::ST7789& driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332& graphics = display.getGraphics();

    sd_card_manager* sd_card_manager = sd_card_manager::get_instance();
    SensorManager& sensor_manager = SensorManager::getInstance();

    Buttons& buttons = Buttons::getInstance();

    const char* path = "0:/measurements/"; // Path to the folder with sensor data

    // List all files in the folder
    DIR dir;
    FILINFO fno;
    FRESULT fr = f_opendir(&dir, path);
    if(fr != FR_OK){
        if (fr == FR_NO_PATH){
            printf("Directory %s does not exist\n", path);
            // Create the directory
            fr = f_mkdir(path);
            f_closedir(&dir);
            return render_del_data();
        } else {
            printf("Failed to open directory %s\n", path);
            printf("Error code: %d\n", fr);
            f_closedir(&dir);
            return;
        }
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
    f_closedir(&dir);

    int file_index = 0;
    int file_count = files.size();

    while(true){
        // Check for button presses
        if (buttons.is_button_b_pressed()){
            file_index = (file_index + 1) % file_count;
        } else if (buttons.is_button_a_pressed()){
            if (file_index == 0){
                file_index = file_count - 1;
            } else {
                file_index--;
            }
        } else if (buttons.is_button_x_pressed()){
            if (file_count == 0){
                printf("No files to delete\n");
                return;
            }
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
        graphics.set_pen(Colors::BLACK);
        graphics.clear();
        graphics.set_pen(Colors::WHITE);

        if (file_count == 0) graphics.text("No files to delete", Point{25, DISPLAY_HEIGHT/2 - 5}, 200, 2);
        graphics.text("Delete file:", Point{25, 10}, 200, 2);
        render_nav_arrows(2, Colors::WHITE);

        graphics.set_pen(Colors::GREEN);
        graphics.text("OK", Point{DISPLAY_WIDTH - 30, 20}, 200, 2);
        graphics.set_pen(Colors::RED);
        graphics.text("CANCEL", Point{DISPLAY_WIDTH - 65, DISPLAY_HEIGHT - 20}, 200, 2);
        graphics.set_pen(Colors::WHITE);

        render_items_list_full_page(file_index, files);

        driver.update(&graphics);
    }
}
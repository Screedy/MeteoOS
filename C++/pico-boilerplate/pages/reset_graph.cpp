//
// Created by Petr Jurásek on 11.07.2024.
//

#include "reset_graph.h"

void render_reset_graph() {
    Display& display = Display::getInstance();
    pimoroni::ST7789& driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332& graphics = display.getGraphics();
    Buttons& buttons = Buttons::getInstance();
    SensorManager& sensor_manager = SensorManager::getInstance();
    sd_card_manager* sd_card_manager = sd_card_manager::get_instance();

    int pin = sensor_manager.getActiveSensor();
    Sensor* sensor = sensor_manager.getSensor(pin);

    while(true){
        if (buttons.is_button_x_pressed()) {
            std::string sensor_name = sensor->getName();
            sensor_name.erase(std::remove(sensor_name.begin(), sensor_name.end(), '\0'), sensor_name.end());
            std::string path = "0:/sensors/measurements/";

            // Delete all files in 0:/sensors/measurements/<sensor_name>_*.txt
            FRESULT res;
            DIR dir;
            FILINFO fno;

            res = f_opendir(&dir, path.c_str());
            if(res != FR_OK){
                printf("Failed to open directory %s\n", path.c_str());
                return;
            }

            for(;;) {
                res = f_readdir(&dir, &fno);
                if (res != FR_OK || fno.fname[0] == 0) break; // Error or end of directory
                if (fno.fattrib & AM_DIR) continue; // Skip directories
                // Check if the file is for the sensor
                std::string file_name = fno.fname;
                if (file_name.find(sensor_name) != std::string::npos) {
                    std::string file_path = path + file_name;
                    res = f_unlink(file_path.c_str());
                    if (res != FR_OK) {
                        printf("Failed to delete file %s\n", file_path.c_str());
                    }
                }
            }
            return;
        } else if (buttons.is_button_y_pressed()) {
            return;
        }

        graphics.set_pen(Colors::BLACK);
        graphics.clear();
        graphics.set_pen(Colors::WHITE);

        graphics.text("Reset graph", Point{2, 0}, 240, 2);
        graphics.text("Are you sure you want to reset the graph for sensor " + sensor->getName() + "?", Point{2, 20}, 160, 2);

        draw_cancel();
        draw_confirm();

        driver.update(&graphics);
    }
}
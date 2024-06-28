//
// Created by Petr Jurásek on 16.06.2024.
//

#include "brightness.h"

#include "../config/sd_card_manager.h"

namespace Brightness{
    Display& display = Display::getInstance();
    pimoroni::ST7789& driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332& graphics = display.getGraphics();
    Buttons& buttons = Buttons::getInstance();
    SensorManager& sensor_manager = SensorManager::getInstance();
}

using namespace Brightness;

// Function to map brightness level from 0-100 to 0-255
int map_brightness(int brightness) {
    return (brightness * 255) / 100;
}

/*
 * Function to save brightness to config file
 * @param brightness - brightness level to save
 *
 * @return void
 */
void save_brightness(int brightness){
    sd_card_manager* sd_card = sd_card_manager::get_instance();
    FIL fil = sd_card->get_fil();
    FRESULT fr;

    //Open file for reading
    fr = f_open(&fil, "0:/config/settings.txt", FA_READ);
    if(fr != FR_OK){
        printf("Failed to open file\n");
        return;
    }

    //Read file
    char buffer[100];
    std::vector<std::string> lines;
    while (f_gets(buffer, sizeof(buffer), &fil)) {
        std::string line(buffer);
        lines.push_back(line);
    }
    f_close(&fil);

    // Replace the brightness line (brightness;value) with the new value
    for (int i = 0; i < lines.size(); i++){
        if (lines[i].find("brightness") != std::string::npos){
            #ifdef TEST_BUILD
            printf("Brightness line found - %s on index (%s)\n", lines[i].c_str(), std::to_string(i).c_str());
            #endif

            lines[i] = "brightness;" + std::to_string(brightness) + "\n";
            break;
        }
        // If the line is not in the file, add it to the end
        if (i == lines.size() - 1){
            lines.push_back("brightness;" + std::to_string(brightness) + "\n");
            #ifdef TEST_BUILD
            printf("Brightness line not found, adding it to the end\n");
            #endif
        }
    }

    fr = f_open(&fil, "0:/config/settings.txt", FA_WRITE | FA_CREATE_ALWAYS);
    if(fr != FR_OK){
        printf("Failed to open file (Writing in save_brightness)\n");
        printf("Error code: %d\n", fr);
        return;
    }

    // Write the modified content back to the file
    for (auto& line : lines) {
        f_puts(line.c_str(), &fil);
    }
    f_close(&fil);

    #ifdef TEST_BUILD
    printf("Brightness saved\n");
    #endif
}

/*
 * Function to load brightness from config file
 *
 * @return int - brightness level from config file (0-100) or 50 if not found
 */
int load_brightness_from_file(){
    sd_card_manager* sd_card = sd_card_manager::get_instance();
    FIL fil = sd_card->get_fil();
    FRESULT fr;

    // Open file for reading
    fr = f_open(&fil, "0:/config/settings.txt", FA_READ);
    if(fr != FR_OK){
        printf("Failed to open file (load_brightness_from_file)\n");
        return -2;
    }

    // Read file
    char buffer[100];
    while (f_gets(buffer, sizeof(buffer), &fil)) {
        std::string line(buffer);
        if (line.find("brightness") != std::string::npos){
            std::string brightness = line.substr(line.find(";") + 1, line.find("\n") - line.find(";") - 1);
            f_close(&fil);
            return std::stoi(brightness);
        }
    }

    f_close(&fil);
    return -1;
}

bool render_brightness(){
    int brightness = load_brightness_from_file();
    brightness = brightness == -1 ? 50 : brightness;

    while (true){
        sleep_ms(250);
        if (buttons.is_button_a_pressed()){
            if (brightness > 90){
                brightness = 10;
            } else {
                brightness+= 10;
            }

            #ifdef TEST_BUILD
            printf("Brightness is going up: %d\n", brightness);
            #endif

            driver.set_backlight(map_brightness(brightness));

        } else if (buttons.is_button_b_pressed()){
            if (brightness <= 10){
                brightness = 100;
            } else {
                brightness-= 10;
            }

            #ifdef TEST_BUILD
            printf("Brightness is going down: %d\n", brightness);
            #endif

            driver.set_backlight(map_brightness(brightness));
        } else if (buttons.is_button_x_pressed()){
            save_brightness(brightness);
            return true;
        } else if (buttons.is_button_y_pressed()){
            return false;
        }

        clear_fast();
        graphics.set_pen(Colors::WHITE);
        graphics.text("Change brightness:", pimoroni::Point{20, 0}, 236, 2);
        render_nav_arrows(0);

        graphics.set_pen(Colors::GREEN);
        graphics.text("OK", Point{DISPLAY_WIDTH - 30, 20}, 200, 2);
        graphics.set_pen(Colors::RED);
        graphics.text("CANCEL", Point{DISPLAY_WIDTH - 65, DISPLAY_HEIGHT - 20}, 200, 2);
        graphics.set_pen(Colors::WHITE);

        render_nice_slider(brightness);
        driver.update(&graphics);
    }
}

void render_nice_slider(int brightness){
    graphics.set_pen(Colors::GRAY);
    graphics.rectangle(pimoroni::Rect{38, 58, 160, 14});

    graphics.set_pen(Colors::WHITE);
    graphics.text("0.1", pimoroni::Point{10, 58}, 236, 2);
    graphics.text("1.0", pimoroni::Point{200, 58}, 236, 2);
    graphics.rectangle(pimoroni::Rect{38, 58, 160 * brightness / 100, 14});
}

void initialize_brightness(){
    int brightness = load_brightness_from_file();

    if (brightness == -1){
        save_brightness(50);
        brightness = 50;
    }

    driver.set_backlight(map_brightness(brightness));

    #ifdef TEST_BUILD
    printf("Brightness initialized\n");
    #endif
}
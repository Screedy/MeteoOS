//
// Created by Petr Jurásek on 21.06.2024.
//


#include "config.h"
#include "setup.h"

void wizard_start(){
    set_defaults();

    // Display the welcome screen
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();

    graphics.clear();
    graphics.set_pen(Colors::WHITE);
    graphics.text("Setup wizard", Point{2, 0}, 240, 2);
    graphics.text("Welcome to your new thermal buddy!\nLet's get everything setup.", Point{2, 20}, 240, 2);
    graphics.text("Press Y to continue", Point{2, DISPLAY_WIDTH - 20}, 240, 2);
    driver.update(&graphics);

    wait_for_y(wizard_start);
}

void pin_setup_render(int pin){
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();

    graphics.clear();
    graphics.set_pen(Colors::WHITE);
    graphics.text("Setup wizard", Point{2, 0}, 240, 2);
    graphics.text("Please select the correct pin for your first thermal sensor with A and B buttons",
                  Point{2, 20}, 236, 2);
    graphics.text("OK", Point{DISPLAY_WIDTH - 25, DISPLAY_HEIGHT - 17}, 236, 2);
    graphics.text("HELP", Point{DISPLAY_WIDTH - 45, 2}, 236, 2);

    clear_pin();
    graphics.text(std::to_string(availablePins[pin]), Point{2, DISPLAY_HEIGHT - 40}, 200, 2);
    driver.update(&graphics);
}

int pin_setup(){
    int pin = 0;

    pin_setup_render(pin);

    Buttons& buttons = Buttons::getInstance();
    while(!buttons.is_button_y_pressed()){
        if (buttons.is_button_x_pressed()){
            help_interrupt();
            pin_setup_render(pin);
        } else if (buttons.is_button_a_pressed()){
            pin = (pin + 1) % availablePins.size();
        } else if (buttons.is_button_b_pressed()){
            if (pin == 0){ // workaround -> modulo not working for negative numbers in C++
                pin = availablePins.size() - 1;
            } else{
                pin--;
            }
        }

        pin_setup_render(pin);
        sleep_ms(150);
    }

    return availablePins[pin];
}

void sd_card_setup(){
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();

    graphics.clear();
    graphics.set_pen(Colors::WHITE);
    graphics.text("Setup wizard", Point{2, 0}, 236, 2);
    graphics.text("Please connect the SD card to the following pins:", Point{2, 20}, 180, 2);
    graphics.text("SCK -> GP10, MOSI -> GP11, MISO -> GP8, CS -> GP9, VCC -> +5V, GND -> GND",
                  Point{2, 70}, 220, 2);
    graphics.text("OK", Point{DISPLAY_WIDTH - 25, DISPLAY_HEIGHT - 17}, 236, 2);
    graphics.text("HELP", Point{DISPLAY_WIDTH - 45, 2}, 236, 2);
    driver.update(&graphics);

    wait_for_y(sd_card_setup);

    //TODO: Test the SD card connection.
}

void help_interrupt(){
    // TODO: QR code.
}

void initial(){
    // Initialize the Display and it's singleton
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();

    wizard_start();
    auto pin = pin_setup();
    std::string pinStr = std::to_string(pin);
    const char* pinCStr = pinStr.c_str(); // Conversion needed for the f_puts function
    sd_card_setup();


    // Initialize the SD card
    auto* sd_card = sd_card_manager::get_instance();

    // Create the config directory and the settings.txt file
    //FATFS fs = sd_card->
    FIL fil = sd_card->get_fil();
    FRESULT fr;

    // Create a directory
    auto path = "0:/config";
    fr = f_mkdir(path);
    if(fr != FR_OK){
        printf("Failed to create directory %s\n", path);
    }

    // Create a file
    path = "0:/config/settings.txt";
    fr = f_open(&fil, path, FA_WRITE | FA_CREATE_ALWAYS);
    if(fr != FR_OK){
        printf("Failed to create file %s\n", path);
    }

    // Write data to the file
    f_puts("PIN: ", &fil);
    f_puts(pinCStr, &fil);
    f_puts("\n", &fil);

    f_puts("STORAGE: ", &fil);
    f_puts("8 9 10 11\n", &fil);

    f_close(&fil);
}

void wait_for_y(std::function<void()> func){ // TODO: Check if this is correct.
    while(true){
        if(Buttons::getInstance().is_button_y_pressed()){
            return;
        } else if(Buttons::getInstance().is_button_x_pressed()){
            help_interrupt();
            func();
        }
    }
}

void clear_pin(){
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();

    graphics.set_pen(Colors::BLACK);
    graphics.rectangle(pimoroni::Rect(2, DISPLAY_HEIGHT-40, 120, DISPLAY_HEIGHT-20));
    graphics.set_pen(Colors::WHITE);
    driver.update(&graphics);
}

void set_defaults(){
    auto* sd_card = sd_card_manager::get_instance();
    auto fil = sd_card->get_fil();
    auto fr = sd_card->get_fr();

    fr = f_open(&fil, "0:/config/settings.txt", FA_WRITE | FA_CREATE_ALWAYS);
    if(fr != FR_OK){
        printf("Failed to open file\n");
        return;
    }

    f_puts("PIN: 0\n", &fil);
    f_puts("STORAGE: 8 9 10 11\n", &fil);

    f_close(&fil);
}

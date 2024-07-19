//
// Created by Petr Jurásek on 21.06.2024.
//


#include "config.h"
#include "setup.h"
#include "../graphics/qrcode_graphics.h"
#include "../pages/add_sensor.h"

void wizard_start(){
    //set_defaults(); //TODO: Look into this later (optional)

    // Display the welcome screen
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();

    graphics.set_pen(Colors::BLACK);
    graphics.clear();
    graphics.set_pen(Colors::WHITE);

    graphics.text("Setup wizard", Point{2, 0}, 240, 2);
    graphics.text("Welcome to your new thermal buddy!\nLet's get everything setup.", Point{2, 20}, 240, 2);
    graphics.text("Press Y to continue", Point{2, DISPLAY_HEIGHT - 20}, 240, 2);
    driver.update(&graphics);

    wait_for_y(wizard_start);
}

void pin_setup_render(int pin){
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();

    graphics.set_pen(Colors::BLACK);
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

    sleep_ms(150);

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

    sleep_ms(150);

    graphics.set_pen(Colors::BLACK);
    graphics.clear();
    graphics.set_pen(Colors::WHITE);

    graphics.text("Setup wizard", Point{2, 0}, 236, 2);
    graphics.text("Please connect the SD card to the following pins:", Point{2, 20}, 220, 2);
    graphics.text("SCK -> GP10, MOSI -> GP11, MISO -> GP8, CS -> GP9, VCC -> +5V, GND -> GND",
                  Point{2, 70}, 220, 2);
    graphics.text("OK", Point{DISPLAY_WIDTH - 25, DISPLAY_HEIGHT - 17}, 236, 2);
    graphics.text("HELP", Point{DISPLAY_WIDTH - 45, 2}, 236, 2);
    driver.update(&graphics);

    #ifdef TEST_BUILD
        printf("Waiting for SD card setup confirm\n");
    #endif

    wait_for_y(sd_card_setup);

    while (!sd_card_manager::get_instance()->is_mounted()){
        graphics.set_pen(Colors::BLACK);
        graphics.clear();

        qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText("https://github.com/Screedy/MeteoOS/tree/main/C%2B%2B",
                                                             qrcodegen::QrCode::Ecc::LOW);

        int left_offset = 80;
        int top_offset = 10;

        draw_qr_code(qr, left_offset, top_offset, 4);

        printf("Failed to mount SD card. Waiting...\n");
        graphics.set_pen(Colors::RED);
        graphics.text("Failed to mount SD card", Point{2, 2}, true);
        driver.update(&graphics);
        sleep_ms(10000);
        sd_card_manager::get_instance()->mount_sd_card();
    }
}

void help_interrupt(){
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();

    graphics.set_pen(Colors::BLACK);
    graphics.clear();
    graphics.set_pen(Colors::WHITE);

    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText("https://github.com/Screedy/MeteoOS/tree/main/C%2B%2B",
                                                         qrcodegen::QrCode::Ecc::LOW);

    draw_qr_code(qr, 10, 10, 4);
    graphics.text("Scan for help", Point{135, 10}, DISPLAY_WIDTH - 135, 2);
    graphics.text("BACK", Point{DISPLAY_WIDTH - 45, DISPLAY_HEIGHT - 17}, 236, 2);

    driver.update(&graphics);

    while(!Buttons::getInstance().is_button_y_pressed()){
        sleep_ms(150);
    }
}

void initial(){

    wizard_start();
    //auto pin = pin_setup(); //Will be changed for the add_sensor page
    //std::string pinStr = std::to_string(pin);
    //const char* pinCStr = pinStr.c_str(); // Conversion needed for the f_puts function
    sd_card_setup();

    // Initialize the SD card
    auto* sd_card = sd_card_manager::get_instance();

    // Create the config directory and the settings.txt file
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

    f_puts("STORAGE: ", &fil);
    f_puts("8 9 10 11\n", &fil);

    f_close(&fil);

    // Create a directory for measurements 0:/sensors/measurements
    path = "0:/sensors/measurements";
    fr = f_mkdir(path);
    if(fr != FR_OK){
        printf("Failed to create directory %s\n", path);
    }

    bool sensor_added = render_add_sensor();
}

void wait_for_y(std::function<void()> func){
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
    auto& graphics = display.getGraphics();

    graphics.set_pen(Colors::BLACK);
    graphics.rectangle(pimoroni::Rect(2, DISPLAY_HEIGHT-40, 120, DISPLAY_HEIGHT-20));
    graphics.set_pen(Colors::WHITE);
}

void set_defaults(){
    sd_card_manager* sd_card = sd_card_manager::get_instance();
    FIL fil = sd_card->get_fil();
    FRESULT fr;

    fr = f_open(&fil, "0:/config/settings.txt", FA_WRITE | FA_CREATE_ALWAYS);
    if(fr != FR_OK){
        printf("Failed to open file\n");
        return;
    }

    f_puts("PIN: 0\n", &fil);
    f_puts("STORAGE: 8 9 10 11\n", &fil);

    f_close(&fil);
}

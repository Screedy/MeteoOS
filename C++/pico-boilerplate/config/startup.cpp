//
// Created by Petr Jurásek on 21.06.2024.
//

#include "startup.h"

#include "sd_card_manager.h"
#include "Display.h"
#include "../sensors/SensorManager.h"
#include "../graphics/qrcode_graphics.h"
#include "../lib/QR-Code-generator/qrcodegen.hpp"
#include "../pages/brightness.h"
#include "rtc_module.h"
#include "hardware/rtc.h"


void sd_card_initialize(){
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();

    // Initialize the SD card. If it fails, the system should not continue.
    // Print an error message on the display and console. The system will be stuck in this loop.
    if(!sd_card_manager::get_instance()->is_mounted()){
        int left_offset = 80;
        int top_offset = 10;
        qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText("https://github.com/Screedy/MeteoOS/tree/main/C%2B%2B",
                                                             qrcodegen::QrCode::Ecc::LOW);

        while(!sd_card_manager::get_instance()->is_mounted()){
            graphics.set_pen(Colors::BLACK);
            graphics.clear();

            draw_qr_code(qr, left_offset, top_offset, 4);

            printf("Failed to mount SD card. Waiting...\n");
            graphics.set_pen(Colors::RED);
            graphics.text("Failed to mount SD card", Point{2, 2}, true);
            driver.update(&graphics);
            sleep_ms(5000);
            sd_card_manager::get_instance()->mount_sd_card();
        }
    }
}

void startup() {
#ifdef TEST_BUILD
    //sleep_ms(5000);
    printf("Starting up\n");
#endif
    // Initialize the Display and it's singleton.
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();
    // Set display to black and clear it.
    graphics.set_pen(Colors::BLACK);
    graphics.clear();
    driver.update(&graphics);

    // Initialize the RTC.
    rtc_init();

    // Initialize the SD card. If it fails, the system should not continue and will wait before an SD card is inserted.
    sd_card_initialize();

    // Set the display's brightness to value in the settings.txt.
    // If there is none, set it to 50% (127) and save it to the file.
    initialize_brightness();

    // Initialize the RTC.
    initialize_rtc();

    #ifdef TEST_BUILD
    printf("Brightness initialized\n");
    printf("Trying to find settings.txt\n");
    #endif

    //Check if 0:/config/settings.txt exists. If not, initialize the setup wizard.
    FRESULT fr;
    FILINFO fno;
    const char *path = "0:/config/settings.txt";
    fr = f_stat(path, &fno);
    #ifdef TEST_BUILD
    printf("Settings file found: %d\n", fr);
    #endif

    if(fr != FR_OK){
        #ifdef TEST_BUILD
        printf("Settings file not found, initializing setup wizard.\n");
        #endif
        initial();
    }

    #ifdef TEST_BUILD
    printf("Settings file found or setup wizard done.\n");
    #endif

    // Check if 0:/sensors/measurements exist. If not, create it.
    path = "0:/sensors/measurements";
    fr = f_stat(path, &fno);
    if(fr != FR_OK){
        fr = f_mkdir(path);
        if(fr != FR_OK){
            printf("Failed to create directory %s\n", path);
        }
    }

    // Initialize the sensor manager. This will load the sensors from the file and initialize them.
    SensorManager* sensor_manager = &SensorManager::getInstance();
}
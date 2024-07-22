//
// Created by Petr Jurásek on 20.07.2024.
//

#include "measurements_tests.h"
#include "../lib/QR-Code-generator/qrcodegen.hpp"
#include "../graphics/graphics.h"
#include "../graphics/qrcode_graphics.h"
#include "../config/sd_card_manager.h"
#include <malloc.h>

void test_generate_qr(int x){
    sleep_ms(2000);

    for(int i = 0; i < 10; i++){
        absolute_time_t start = get_absolute_time();
        qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText("Hello, world! 1234567890", qrcodegen::QrCode::Ecc::LOW);
        absolute_time_t end = get_absolute_time();
        int64_t elapsed = absolute_time_diff_us(start, end);
        double elapsed_seconds = elapsed / 1000000.0;
        printf("QR code generation took %f seconds\n", elapsed_seconds);
    }
}

void test_render_qr(){
    sleep_ms(2000);

    for(int i = 0; i < 10; i++){
        absolute_time_t start = get_absolute_time();

        // -------- code tested -------------
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
        // -------- code tested -------------

        absolute_time_t end = get_absolute_time();
        int64_t elapsed = absolute_time_diff_us(start, end);
        double elapsed_seconds = elapsed / 1000000.0;
        printf("QR code rendering took %f seconds\n", elapsed_seconds);


    }
}

void test_storage(int x){
    sleep_ms(2000);

    for(int i = 0; i < x; i++){
        absolute_time_t start = get_absolute_time();

        // -------- code tested -------------

        test_storage_body();

        // -------- code tested -------------

        absolute_time_t end = get_absolute_time();
        int64_t elapsed = absolute_time_diff_us(start, end);
        double elapsed_seconds = elapsed / 1000000.0;
        printf("SD card initialization took %f seconds\n", elapsed_seconds);
    }

    //Mount the sd card back.
    auto* sd_card_manager = sd_card_manager::get_instance();
    sd_card_manager->mount_sd_card();
}

void test_storage_body(){
    auto* sd_card_manager = sd_card_manager::get_instance();

    if(sd_card_manager->is_mounted()){
        sd_card_manager->unmount_sd_card();
    }

    sd_card_manager->mount_sd_card();

    // Test writing to SD card
    FIL fil = sd_card_manager->get_fil();
    FRESULT res = f_open(&fil, "0:/test.txt", FA_WRITE | FA_CREATE_ALWAYS);

    if (res != FR_OK) {
        printf("Failed to open file\n");
        return;
    }

    const char* text = "Test writing to SD card";

    if (f_printf(&fil, text) < 0) {
        printf("Failed to write to file\n");
        return;
    }

    f_close(&fil);

    // Test reading from SD card
    res = f_open(&fil, "0:/test.txt", FA_READ);

    if (res != FR_OK) {
        printf("Failed to open file\n");
        return;
    }

    char buffer[100];
    f_gets(buffer, sizeof(buffer), &fil);
    f_close(&fil);

    if (strcmp(buffer, text) != 0) {
        printf("Text read from file is not the same\n");
        return;
    }

    // Test deleting file
    res = f_unlink("0:/test.txt");
    if (res != FR_OK) {
        printf("Failed to delete file\n");
        return;
    }

    sd_card_manager->unmount_sd_card();
}

void test_list_dir(int x){
    sleep_ms(2000);

    for(int i = 0; i < x; i++){
        absolute_time_t start = get_absolute_time();

        // -------- code tested -------------

        auto* sd_card_manager = sd_card_manager::get_instance();

        if(!sd_card_manager->is_mounted()){
            sd_card_manager->mount_sd_card();
        }

        DIR dir;
        FRESULT res = f_opendir(&dir, "0:/");

        if (res != FR_OK) {
            printf("Failed to open directory\n");
            return;
        }

        FILINFO fno;
        while (f_readdir(&dir, &fno) == FR_OK && fno.fname[0]) {
            printf("%s, ", fno.fname);
        }

        printf("\n");

        f_closedir(&dir);

        // -------- code tested -------------

        absolute_time_t end = get_absolute_time();
        int64_t elapsed = absolute_time_diff_us(start, end);
        double elapsed_seconds = elapsed / 1000000.0;
        printf("Listing files took %f seconds\n", elapsed_seconds);
    }
}

uint32_t getTotalHeap(void) {
    extern char __StackLimit, __bss_end__;

    return &__StackLimit  - &__bss_end__;
}

uint32_t getFreeHeap(void) {
    struct mallinfo m = mallinfo();

    return getTotalHeap() - m.uordblks;
}
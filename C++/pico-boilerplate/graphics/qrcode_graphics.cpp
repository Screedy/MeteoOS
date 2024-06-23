//
// Created by Petr Jurásek on 23.06.2024.
//

#include "qrcode_graphics.h"
#include "../config/Display.h"
#include "../config/config.h"

void draw_qr_code(qrcodegen::QrCode &qr, int x_offset, int y_offset, int scale) {
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();

    // Draw the QR code on the display.
    graphics.set_pen(Colors::BLACK);
    graphics.clear();
    graphics.set_pen(Colors::WHITE);
    for(int y = 0; y < qr.getSize(); y++) {
        for(int x = 0; x < qr.getSize(); x++) {
            if(qr.getModule(x, y)) {
                graphics.rectangle(pimoroni::Rect(x * scale + x_offset, y * scale + y_offset, scale, scale));
            }
        }
    }
    driver.update(&graphics);
}

void render_help(const char *message){
    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(message, qrcodegen::QrCode::Ecc::LOW);

    int left_offset = DISPLAY_WIDTH / 2 - (qr.getSize() / 2);
    int top_offset = DISPLAY_HEIGHT / 2 - (qr.getSize() / 2);

    draw_qr_code(qr, 10, 10, 4);
}
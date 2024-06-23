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
    for(int y = 0; y < qr.getSize(); y++) {
        for(int x = 0; x < qr.getSize(); x++) {
            if(qr.getModule(x, y)) {
                graphics.rectangle(pimoroni::Rect(x * scale + x_offset, y * scale + y_offset, scale, scale));
            }
        }
    }
}

void render_help(const char *message, int left_offset, int top_offset) {
    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(message, qrcodegen::QrCode::Ecc::LOW);

    draw_qr_code(qr, 10, 10, 4);
}
//
// Created by Petr Jurásek on 23.06.2024.
//

#ifndef PICO_BOILERPLATE_QRCODE_GRAPHICS_H
#define PICO_BOILERPLATE_QRCODE_GRAPHICS_H

#include "../lib/QR-Code-generator/qrcodegen.hpp"

/*
 * Function that draws the QR code on the display.
 * @param qr The QR code to be drawn.
 * @return None.
 */
void draw_qr_code(qrcodegen::QrCode &qr, int x_offset, int y_offset, int scale);

/*
 * Function that renders the QR code on the display.
 * @param message The message to be rendered.
 * @return None.
 */
void render_help(const char *message, int left_offset, int top_offset);


#endif //PICO_BOILERPLATE_QRCODE_GRAPHICS_H

//
// Created by Petr Jurásek on 20.07.2024.
//

#ifndef METEOOS_MEASUREMENTS_TESTS_H
#define METEOOS_MEASUREMENTS_TESTS_H

#include "pico/stdlib.h"
#include "hardware/timer.h"

#include <vector>
#include <cstdio>
#include <cstring>

/*
 * Function that tests the generation of a QR code and only that. This test isolates the QR code generation from
 * the rendering of the page. It measures the time it takes to generate a QR code x times.
 */
void test_generate_qr(int x);

void test_render_qr();

void test_storage(int x);

void test_storage_body();

void test_list_dir(int x);

uint32_t getTotalHeap(void);

uint32_t getFreeHeap(void);

#endif //METEOOS_MEASUREMENTS_TESTS_H

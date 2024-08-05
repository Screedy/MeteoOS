//
// Created by Petr Jurásek on 02.07.2024.
//

#include "set_time.h"

#include "../config/config.h"
#include "../graphics/graphics.h"
#include "../graphics/page_elements.h"

void x_button_text(uint8_t setting){
    if (setting == 5){
        draw_ok();
    } else {
        draw_next();
    }
}

void y_button_text(uint8_t setting){
    if (setting == 0){
        draw_back();
    } else {
        draw_prev();
    }
}

// Function to determine if a year is a leap year
bool is_leap_year(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    } else {
        return false;
    }
}

// Function to get the number of days in a month
int days_in_month(int month, int year) {
    static const std::array<int, 12> days_in_months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) {
        return 29;
    }
    return days_in_months[month - 1];
}

// Function to increment the day in a datetime_t
void increment_day(datetime_t *dt){
    int days = days_in_month(dt->month, dt->year);
    dt->day = (dt->day % days) + 1;
}

void decrement_day(datetime_t *dt){
    int days = days_in_month(dt->month, dt->year);
    if (dt->day == 1){
        dt->day = days;
    } else {
        dt->day--;
    }
}

void render_set_time_menu() {
    Display& display = Display::getInstance();
    pimoroni::ST7789& driver = display.getDriver();
    pimoroni::PicoGraphics_PenRGB332& graphics = display.getGraphics();

    Buttons& buttons = Buttons::getInstance();

    datetime_t dt = get_current_datetime();
    if (dt.year < 1999){
        dt.year = 2024;
        dt.month = 1;
        dt.day = 1;
        dt.dotw = 0;
        dt.hour = 0;
        dt.min = 0;
        dt.sec = 0;
    }

    // Define the rectangles for each part of the datetime_t
    const std::array<Rect, 6> rectangles = {
            Rect{60, DISPLAY_HEIGHT/2, 45, 15},
            Rect{120, DISPLAY_HEIGHT/2, 23, 15},
            Rect{155, DISPLAY_HEIGHT/2, 23, 15},
            Rect{60, DISPLAY_HEIGHT/2 + 15, 23, 15},
            Rect{95, DISPLAY_HEIGHT/2 + 15, 23, 15},
            Rect{130, DISPLAY_HEIGHT/2 + 15, 23, 15}
    };

    uint8_t setting = 0; // Which part of the datetime_t is currently being set

    while(true){
        // Logic for setting the time
        if(buttons.is_button_a_held()){
            switch (setting) {
                case 0:
                    dt.year++;
                    break;
                case 1:
                    dt.month = (dt.month % 12) + 1;
                    break;
                case 2:
                    increment_day(&dt);
                    break;
                case 3:
                    dt.hour = (dt.hour + 1) % 24;
                    break;
                case 4:
                    dt.min = (dt.min + 1) % 60;
                    break;
                case 5:
                    dt.sec = (dt.sec + 1) % 60;
                    break;
            }
        }
        else if(buttons.is_button_b_held()){
            switch (setting){
                case 0:
                    dt.year = (dt.year == 2000) ? dt.year : dt.year - 1;
                    break;
                case 1:
                    dt.month = (dt.month == 1) ? 12 : dt.month - 1;
                    break;
                case 2:
                    decrement_day(&dt);
                    break;
                case 3:
                    dt.hour = (dt.hour == 0) ? 23 : dt.hour - 1;
                    break;
                case 4:
                    dt.min = (dt.min == 0) ? 59 : dt.min - 1;
                    break;
                case 5:
                    dt.sec = (dt.sec == 0) ? 59 : dt.sec - 1;
                    break;
            }
        }
        else if(buttons.is_button_y_pressed()){
            if(setting == 0){
                return; // Exit if backing up on the first setting.
            } else {
                setting--;
            }
        }
        else if (buttons.is_button_x_pressed()){
            if(setting == 5){
                int dotw = calculate_dotw(dt.day, dt.month, dt.year);
                dt.dotw = dotw;
                set_time(&dt); // Set the time if the last setting is reached.
                return;
            } else {
                setting++;
            }
        }

        // Render the page
        graphics.set_pen(Colors::BLACK);
        graphics.clear();
        graphics.set_pen(Colors::WHITE);

        render_nav_arrows(6);
        graphics.text("Set date", Point{35, 10}, 236, 2);

        //Set graphics for everything except the one that is being set:
        char buffer[256];

        // Set gray square around the setting that is being set
        graphics.set_pen(Colors::GRAY);
        // Render the correct gray rectangle overlay
        graphics.rectangle(rectangles[setting]);
        // Render the correct text
        x_button_text(setting);
        y_button_text(setting);

        graphics.set_pen(Colors::WHITE);
        snprintf(buffer, 256, "%04d.%02d.%02d\n%02d:%02d:%02d", dt.year, dt.month, dt.day, dt.hour, dt.min, dt.sec);
        graphics.text(buffer, Point{60, DISPLAY_HEIGHT/2}, 236, 2, 0, 0, true);


        driver.update(&graphics);
    }
}
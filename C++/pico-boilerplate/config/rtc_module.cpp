//
// Created by Petr Jurásek on 02.07.2024.
//

#include "rtc_module.h"

void initialize_rtc() {
    rtc_init();
}

datetime_t get_current_datetime() {
    datetime_t datetime;
    rtc_get_datetime(&datetime);
    return datetime;
}

void set_time(datetime_t* datetime) {
    rtc_set_datetime(datetime);
}

bool is_rtc_set(){
    datetime_t datetime;
    rtc_get_datetime(&datetime);

    if (datetime.year < 1999){
        return false;
    }
    return true;
}

std::string get_format_time(datetime_t datetime){
    std::string time = "";
    time += datetime.hour < 10 ? "0" + std::to_string(datetime.hour) : std::to_string(datetime.hour);
    time += ":";
    time += datetime.min < 10 ? "0" + std::to_string(datetime.min) : std::to_string(datetime.min);
    return time;
}

datetime_t start_of_week(datetime_t datetime){
    datetime_t dt = datetime;
    // Calculate the day of the week
    int dotw = calculate_dotw(dt.day, dt.month, dt.year);

    // Calculate the difference between the current day and the start of the week
    int diff = dotw;
    if (diff != 0){
        diff = -diff; // If the day is not Monday, we need to go back to previous monday
    }

    dt.day += diff;

    // Handle month and year adjustments if necessary
    while (dt.day <= 0){
        dt.month--;
        if (dt.month <= 0) {
            dt.month = 12;
            dt.year--;
        }
        // Set the day to the last day of the previous month
        if (dt.month == 1 || dt.month == 3 || dt.month == 5 || dt.month == 7 ||
        dt.month == 8 || dt.month == 10 || dt.month == 12) {
            dt.day += 31;
        } else if (dt.month == 4 || dt.month == 6 || dt.month == 9 || dt.month == 11) {
            dt.day += 30;
        } else {
            if ((dt.year % 4 == 0 && dt.year % 100 != 0) || (dt.year % 400 == 0)) {
                dt.day += 29; // Leap year
            } else {
                dt.day += 28;
            }
        }
    }

    dt.dotw = calculate_dotw(dt.day, dt.month, dt.year);

    return dt;
}

int calculate_dotw(int day, int month, int year){
    // Zeller's Congruence algorithm
    if (month < 3){
        month += 12;
        year--;
    }

    int K = year % 100;
    int J = year / 100;
    int f = day + (13 * (month + 1)) / 5 + K + K / 4 + J / 4 + 5 * J;
    int dotw = f % 7;

    // Convert Zeller's output to our format (0 is Monday, 6 is Sunday)
    return (dotw + 6) % 7;
}

int getNumDaysInMonth(int month, int year){
    if (month == 1 || month == 3 || month == 5 || month == 7 ||
        month == 8 || month == 10 || month == 12) {
        return 31;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return 29; // Leap year
        } else {
            return 28;
        }
    }
}
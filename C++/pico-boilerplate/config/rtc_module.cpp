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

    #ifdef TEST_BUILD
    //printf("RTC year: %d\n", datetime.year);
    #endif

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
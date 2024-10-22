//
// Created by Petr Jurásek on 02.07.2024.
//

#ifndef PICO_BOILERPLATE_RTC_MODULE_H
#define PICO_BOILERPLATE_RTC_MODULE_H

#include <stdio.h>
#include <string>

#include "pico/stdlib.h"
#include "hardware/rtc.h"

/*
 * Structure that represents a date and time of the RTC.
 * Contains the year, month, day, day of the week, hour, minute and second.
 *
 * @param year The year of the date.
 * @param month The month of the date.
 * @param day The day of the date.
 * @param dotw The day of the week (0 is Monday, 6 is Sunday).
 * @param hour The hour of the time.
 * @param min The minute of the time.
 * @param sec The second of the time.
 */
/*struct datetime_t {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t dotw;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
};*/

/*
 * Function that initializes the RTC with a specified data and time.
 *
 *
 * @return None.
 */
void initialize_rtc();

/*
 * Function that returns the current time.
 *
 * @return The current time.
 */
datetime_t get_current_datetime();

/*
 * Function that sets the time of the RTC.
 *
 * @param datetime The time to be set. Example:
 * datetime_t t = {
 *      .year = 2024,   // Year of the date
 *      .month = 1,     // Month of the date
 *      .day = 1,       // Day of the date
 *      .dotw = 0,      // Day of the week (0 is Monday, 6 is Sunday)
 *      .hour = 1,      // Hour of the time
 *      .min = 0,       // Minute of the time
 *      .sec = 0        // Second of the time
 * };
 *
 * @return None.
 */
void set_time(datetime_t* datetime);

/*
 * Function that checks if the RTC is set.
 *
 * @return True if the RTC is set, false otherwise.
 */
bool is_rtc_set();

/*
 * Function that returns the current time in the format "HH:MM".
 *
 * @param datetime The time to be formatted.
 *
 * @return The formatted time.
 */
std::string get_format_time(datetime_t datetime);

/*
 * For a given date, calculate the start of the week.
 *
 * @param datetime The date for which to calculate the start of the week.
 * @return datetime_t The start of the week for the given date.
 *
 * @example For the date 2024-07-12 (Friday), the start of the week is 2024-07-08 (Monday).
 */
datetime_t start_of_week(datetime_t datetime);

/*
 * Function that calculates the day of the week for a given date.
 * Uses the Zeller's Congruence algorithm.
 *
 * @param day The day of the date.
 * @param month The month of the date.
 * @param year The year of the date.
 *
 * @return The day of the week (0 is Monday, 6 is Sunday).
 */
int calculate_dotw(int day, int month, int year);

/*
 * Function that returns the number of days in a given month.
 *
 * @param month The month for which to calculate the number of days.
 * @param year The year for which to calculate the number of days.
 *
 * @return The number of days in the given month.
 */
int getNumDaysInMonth(int month, int year);

#endif //PICO_BOILERPLATE_RTC_MODULE_H

//
// Created by Petr Jurásek on 09.07.2024.
//

#include "strategy_graph_interval.h"

#include "../../config/sd_card_manager.h"
#include "../../utils/string_modifiers.h"

float StrategyGraphInterval::getMin(const std::vector<float>& values) {
    float min = std::numeric_limits<float>::max();
    for (float value : values) {
        if (value != -404.0f && value < min) {
            min = value;
        }
    }
    return min;
}

float StrategyGraphInterval::getMax(const std::vector<float>& values) {
    float max = std::numeric_limits<float>::min();
    for (float value : values) {
        if (value != -404.0f && value > max) {
            max = value;
        }
    }
    return max;
}

int StrategyGraphInterval::temperature_to_pixel(float temp, float min_temp, float max_temp) {
    int pixel_min = 20;
    int pixel_max = 100;

    #ifdef TEST_BUILD
        //printf("The pixel y value is: %d\n", (int) (pixel_max + ((temp - min_temp) * (pixel_min - pixel_max)) / (max_temp - min_temp)));
    #endif

    if (min_temp == max_temp) {
        return 60;
    }

    return (int) (pixel_min + ((temp - min_temp) * (pixel_max - pixel_min)) / (max_temp - min_temp));
}

std::array<float, 2> StrategyGraphInterval::generateOneDayValues(datetime_t day, FIL& file) {
    std::array<float, 2> values;
    values[0] = 0.0f;
    values[1] = 0.0f;
    int count = 0;
    int rollbacks_chars = 0;

    sd_card_manager *sd_card_manager = sd_card_manager::get_instance();

    // Read n lines from the file, if the day on the line is the same as the given day
    // Calculate the average temperature and humidity for that day. Read until the day changes or the end of
    // the file is reached. Return the average temperature and humidity for that day.
    std::vector <std::string> lines;
    sd_card_manager->read_n_lines(file, 50, lines);
    while (!lines.empty()) {
        #ifdef TEST_BUILD
        printf("Lines: %d\n", lines.size());
        #endif

        for (auto line: lines) {
            // Format of one line is: (2024, 2, 12, 0, 21, 18, 38, 0);22;30
            std::vector <std::string> parts = split(line, ';');

            std::string date_part = parts[0];
            date_part.erase(std::remove(date_part.begin(), date_part.end(), '('), date_part.end());
            date_part.erase(std::remove(date_part.begin(), date_part.end(), ')'), date_part.end());

            std::vector <std::string> date_parts = split(date_part, ',');
            uint16_t line_year = std::stoi(date_parts[0]);
            uint8_t line_month = std::stoi(date_parts[1]);
            uint8_t line_day = std::stoi(date_parts[2]);

            datetime_t line_date;
            line_date.year = line_year;
            line_date.month = line_month;
            line_date.day = line_day;

            #ifdef TEST_BUILD
            printf("Line: %s\n", line.c_str());
            //sleep_ms(1000);
            #endif
            // Check if the day is before the given day
            if (compare_date(day, line_date) > 0){
                #ifdef TEST_BUILD
                printf("The day is before the given day\n");
                //printf("Line day: %d, Line month: %d, Line year: %d\n", line_day, line_month, line_year);
                //printf("Given day: %d, Given month: %d, Given year: %d\n", day.day, day.month, day.year);
                //sleep_ms(1000);
                #endif
                continue; // Skip the line
            }

            if (compare_date(day, line_date) < 0){
                #ifdef TEST_BUILD
                printf("The day is after the given day\n");
                //sleep_ms(1000);
                #endif
                rollbacks_chars = line.length();
                continue; // End of the day
            }

            #ifdef TEST_BUILD
            printf("The day is the same as the given day\n");
            //sleep_ms(1000);
            #endif

            // The day is the same as the given day
            values[0] += std::stof(parts[1]);
            values[1] += std::stof(parts[2]);

            count++;
        }

        if (rollbacks_chars > 0) {
            f_lseek(&file, f_tell(&file) - rollbacks_chars);
            break; // End of the day
        }

        lines.clear();
        sd_card_manager->read_n_lines(file, 50, lines);
    }

    #ifdef TEST_BUILD
    printf("temperature for the day is: %f\n", values[0]);
    printf("humidity for the day is: %f\n", values[1]);
    //sleep_ms(4000);
    #endif

    if (count != 0) {
        values[0] /= count;
        values[1] /= count;
    } else {
        values[0] = -404.0f;
        values[1] = -404.0f;
    }

    #ifdef TEST_BUILD
    printf("The average temperature for the day is: %f\n", values[0]);
    printf("The average humidity for the day is: %f\n", values[1]);
    #endif

    #ifdef TEST_GRAPH_INTEGRITY
        printf("The count of lines for this day is: %d\n", count);
    #endif

    return values;
}

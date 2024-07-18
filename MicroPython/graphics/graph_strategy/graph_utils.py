# from gc import collect

from config.config import Colors, Display
from utils.file_operations import read_n_lines, file_exists
from utils.date_operations import compate_dates, start_of_week


def day_data(date, file):
    """Returns the average data for the given day.

    :param date: The day to get the data from in a format of a tuple (year, month, day).
    :param file: The file to get the data from.
    :return: A tuple containing the average measurements for the given day.
    :OSError: If the SD card is not mounted.
    """

    temp_sum = 0
    hum_sum = 0
    count = 0

    # collect()

    while True:
        lines = read_n_lines(file, 50)
        rollback_chars = 0

        if not lines:
            break

        for line in lines:
            date_file, temp_file, hum_file = line.split(";")
            date_file = date_file.replace("(", "").replace(" ", "").replace(")", "").split(",")

            date_file = tuple(map(int, date_file))

            if compate_dates(date, date_file) == 0:
                temp_sum += float(temp_file)
                hum_sum += float(hum_file)
                count += 1

            if compate_dates(date, date_file) == -1:
                rollback_chars += len(line)

        if rollback_chars:
            file.seek(-rollback_chars, 1)
            break

        # if env_vars['TEST_GRAPH_MEMORY'] and date[3] == 2 and count == 500:
            # pass
            # ram_after_500_lines_third_day = gc.mem_free()
            # print("RAM after 500 lines on the third day:", ram_after_500_lines_third_day)

    print(temp_sum, hum_sum, count)

    # if env_vars['TEST_GRAPH_MEMORY'] and date[3] == 0:
        # pass
        # ram_after_first_day = gc.mem_free()
        # print("RAM after first day:", ram_after_first_day)

    if count == 0:
        return -404, -404
    return temp_sum / count, hum_sum / count


def days_data(day_of_week, target_sensor):
    """Returns the average data for the given days in a week.

    :param day_of_week: The day to get the data from in a format of a tuple (year, month, day, weekday).
    :param target_sensor: The sensor to get the data from.
    :return: A tuple containing the average measurements for the given days in a week.
    """

    start = start_of_week(day_of_week)
    temp = [0, 0, 0, 0, 0, 0, 0]
    hum = [0, 0, 0, 0, 0, 0, 0]

    if not file_exists(target_sensor):
        return temp, hum

    with open("sd/measurements/" + target_sensor.name + ".txt", "r") as fr:
        for i in range(7):
            temp[i], hum[i] = day_data((day_of_week[0], day_of_week[1], start + i), fr)

    return temp, hum


def week_data(day, target_sensor):
    """Returns the temperature and humidity data for the given month.

    :param day: The day to reference the week to. If set to Friday 16th of the month, the graph_strategy will
    start at the start of the month and end at the end of the month.
    :param target_sensor: The sensor to get the data from.
    :return: Two lists containing the temperature and humidity data for the given month.
    """

    temp = [0, 0, 0, 0]
    hum = [0, 0, 0, 0]

    if not file_exists(target_sensor):
        return temp, hum

    with open("sd/measurements/" + target_sensor.name + ".txt", "r") as fr:
        for i in range(4):
            temp[i], hum[i] = weeks_data((day[0], day[1], 1 + i * 7), fr)

    return temp, hum


def weeks_data(day, file):
    """Returns the average data for the given week.

    :param day: The day to reference the week to. If set to Friday 16th of the month, the graph_strategy will
    start at the start of the month and end at the end of the month.
    :param file: The file to get the data from.
    :return: A tuple containing the average measurements for the given week.
    """

    temp_sum = 0
    hum_sum = 0
    count = 0

    for i in range(7):
        temp, hum = day_data((day[0], day[1], day[2] + i), file)

        if temp != -404:
            temp_sum += temp
            count += 1

        if hum != -404:
            hum_sum += hum

    if count == 0:
        return -404, -404
    return temp_sum / count, hum_sum / count


def get_measurements(target_sensor):
    """Returns the measurements for the given sensor from a file.

    :param target_sensor: The sensor to get the measurements for.
    :return: Two lists containing the temperature and humidity measurements.
    """

    with open("/sensors/measurements/" + target_sensor.name + "daily.txt", "r") as fr:
        line = fr.readline()
        temp, hum = line.split(";")

    temp = temp.replace("[", "").replace("]", "").split(", ")
    hum = hum.replace("[", "").replace("]", "").split(", ")

    for i in range(len(temp)):
        temp[i] = float(temp[i])
        hum[i] = float(hum[i])

    return temp, hum


def render_temp_values(max_temp, min_temp, max_hum, min_hum):
    """Renders the maximum, middle and minimum temperature values on the display."""

    disp = Display()
    disp().set_pen(Colors.WHITE)

    temp_middle = max_temp - (max_temp - min_temp) / 2

    disp().text(str(round(max_temp, 1)), 108, 20, 250, 1)
    disp().text(str(round(temp_middle, 1)), 108, 60, 250, 1)
    disp().text(str(round(min_temp, 1)), 108, 98, 250, 1)

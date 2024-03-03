# 125 pixels
import utime
from config.config import *
import page_elements
from config.sdcard_manager import SDCardManager
import sensors.sensor_manager as sm


class StrategyGraphInterval:
    """The strategy interface for rendering the graph."""

    def render_graph(self, date, sensor, force=False) -> None:
        """Renders the graph using the strategy pattern.

        :param date: The day to reference the graph to.
        :param sensor: The sensor to get the data from.
        :param force: If set to True, the graph will be rendered from the file again and not from memory.
        """

        pass


class ConcreteStrategyDaily(StrategyGraphInterval):
    """The concrete strategy for rendering the daily graph."""

    def render_graph(self, date, sensor, force=False) -> None:
        """Renders the daily graph using the strategy pattern.

        :param date: The day to referer the week to. If set to Friday 16th of the month, the graph will
        display a week from 12th to 18th.
        :param sensor: The sensor to get the data from.
        :param force: If set to True, the graph will be rendered from the file again and not from memory.
        :return: None
        """

        display = Display()

        display().text("MO TU WE TH FR SA SU", 130, 105, 250, 1)

        if force:
            temp, hum = days_data(date, sensor)

            with open("/sensors/measurements/" + sensor.name + "daily.txt", "w") as fw:
                fw.write(f"{temp};{hum}")
        else:
            temp, hum = get_measurements(sensor)

        render_daily_graph((list(temp)), list(hum))


class ConcreteStrategyWeekly(StrategyGraphInterval):
    """The concrete strategy for rendering the weekly graph."""

    def render_graph(self, date, sensor, force=False) -> None:
        """Renders the weekly graph using the strategy pattern.

        :param date: The day to referer the month to. If set to 16th of January, the graph will be
        displayed from 1st to 31st of January.
        :param sensor: The sensor to get the data from.
        :param force: If set to True, the graph will be rendered from the file again and not from memory.
        :return: None
        """

        display = Display()

        display().text("WEEK1 WEEK2 WEEK3 WEEK4", 130, 105, 250, 1)

        if force:
            temp, hum = week_data(date, sensor)

            with open("/sensors/measurements/" + sensor.name + "weekly.txt", "w") as fw:
                fw.write(f"{temp};{hum}")
        else:
            temp, hum = get_measurements(sensor)

        render_weekly_graph((list(temp)), list(hum))


class ContextGraphInterval():
    """The context class for the strategy pattern to render the graphs."""

    _strategy = None
    _data = None

    def __init__(self, strategy) -> None:
        """Initializes the context class with the strategy.

        :param strategy: The strategy to use for rendering the graph.
        """

        self._strategy = strategy

    @property
    def strategy(self) -> StrategyGraphInterval:
        """The strategy to use for rendering the graph."""

        return self._strategy

    @strategy.setter
    def strategy(self, strategy: StrategyGraphInterval) -> None:
        """Sets the strategy to use for rendering the graph."""

        self._strategy = strategy
        self._data = None

    def render_graph(self, date, sensor, force=False) -> None:
        """Renders the graph using the strategy pattern."""

        display = Display()

        display().set_pen(Colors.WHITE)
        display().line(125, 103, 234, 103, 1)
        display().line(125, 103, 125, 20, 1)

        self._strategy.render_graph(date, sensor, force)

        display().update()


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

    # year, month, day = str(date[0]), str(date[1]), str(date[2])

    while True:
        lines = read_n_lines(file, 350)
        rollback_chars = 0

        if not lines:
            break

        for line in lines:
            print("-------------------")
            # print(line)
            date_file, temp_file, hum_file = line.split(";")
            date_file = date_file.replace("(", "").replace(" ", "").replace(")", "").split(",")

            date_file = tuple(map(int, date_file))

            print(date_file, temp_file, hum_file)
            # print(year, month, day)
            print("-------------------")

            if compate_dates(date, date_file) == 0:
                temp_sum += float(temp_file)
                hum_sum += float(hum_file)
                count += 1

            if compate_dates(date, date_file) == -1:
                rollback_chars += len(line)

        if rollback_chars:
            # print(f"Seeking back {rollback_chars}.")
            file.seek(-rollback_chars, 1)
            break

    print(temp_sum, hum_sum, count)

    if count == 0:
        return -404, -404
    return temp_sum / count, hum_sum / count


def days_data(day_of_week, sensor):
    """Returns the average data for the given day in a week.

    :param day_of_week: The day to get the data from in a format of a tuple (year, month, day, weekday).
    :param sensor: The sensor to get the data from.
    :return: A tuple containing the average measurements for the given day.
    """

    start = start_of_week(day_of_week)
    temp = [0, 0, 0, 0, 0, 0, 0]
    hum = [0, 0, 0, 0, 0, 0, 0]

    if not file_exists(sensor):
        return temp, hum

    with open("sd/measurements/" + sensor.name + ".txt", "r") as fr:
        for i in range(7):
            temp[i], hum[i] = day_data((day_of_week[0], day_of_week[1], start + i), fr)

    return temp, hum


def week_data(day, sensor):
    """Returns the temperature and humidity data for the given month.

    :param day: The day to reference the week to. If set to Friday 16th of the month, the graph will
    start at the start of the month and end at the end of the month.
    :param sensor: The sensor to get the data from.
    :return: Two lists containing the temperature and humidity data for the given month.
    """

    temp = [0, 0, 0, 0]
    hum = [0, 0, 0, 0]

    if not file_exists(sensor):
        return temp, hum

    with open("sd/measurements/" + sensor.name + ".txt", "r") as fr:
        for i in range(4):
            temp[i], hum[i] = weeks_data((day[0], day[1], 1 + i * 7), fr)

    return temp, hum


def weeks_data(day, file):
    """Returns the average data for the given week.

    :param day: The day to reference the week to. If set to Friday 16th of the month, the graph will
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


def read_n_lines(file, n: int):
    """Reads n lines from the given file. If the file has less than n lines, it will read all the lines.
    Stops the measurements while reading the file to prevent the SD card from crashing.

    :param file: The file to read from.
    :param n: The number of lines to read.
    :return: A list containing the read lines.
    """

    lines = []

    pause_all_measurements()

    for i in range(n):
        line = file.readline()

        if not line:
            break

        lines.append(line)

    resume_all_measurements()
    return lines


def file_exists(sensor):
    """Checks if the file for the given sensor exists on the SD card.

    :param sensor: The sensor to check the file for.
    :return: True if the file exists, False otherwise.
    """

    try:
        sd = SDCardManager()
        sd.mount()
        files = sd.list_files("/sd/measurements")
    except OSError:
        raise OSError("SD card is not mounted")

    if f"{sensor.name}.txt" not in files:
        raise OSError(f"File {sensor.name}.txt not found on the SD card")

    return True


def pause_all_measurements():
    """Pauses all measurements to be saved to the SD card. This is a necessary step before loading huge data from the
    SD card because it may take a while to load the data and it would cause the SD card to crash.

    :return: None
    """

    sensor_manager = sm.SensorManager()

    for sensor in sensor_manager.sensors:
        sensor.pause_measure()


def resume_all_measurements():
    """Resumes all measurements to be saved to the SD card. This is a necessary step after loading huge data from the
    SD card because it may take a while to load the data and it would cause the SD card to crash.

    :return: None
    """

    sensor_manager = sm.SensorManager()

    for sensor in sensor_manager.sensors:
        sensor.resume_measure()


def start_of_week(day):
    """Returns the start of the week for the given day.

    :param day: The day to reference the week to. Needs to be in a format of a tuple (year, month, day, weekday)
    :return: The start of the week for the given day.
    """

    day_in_week = day[3]

    return day[2] - day_in_week


def compate_dates(date1, date2):
    """Compares the two given dates.

    :param date1: The first date to compare. Format: (year, month, day)
    :param date2: The second date to compare. Format: (year, month, day)
    :return: 0 if date1 is equal to date2, 1 if date1 is greater than date2, -1 if date1 is less than date2.
    """

    if date1[0] > date2[0]:
        return 1
    elif date1[0] < date2[0]:
        return -1

    if date1[1] > date2[1]:
        return 1
    elif date1[1] < date2[1]:
        return -1

    if date1[2] > date2[2]:
        return 1
    elif date1[2] < date2[2]:
        return -1

    return 0


def seek_back_one_line(file):
    """Seeks back one line in the given file.

    :param file: The file to seek back one line in.
    :return: None
    """

    file.seek(-1, 1)

    if file.tell() == 0:
        return

    while file.read(1) != b"\n" and file.tell() > 0:
        file.seek(-2, 1)

    if file.tell() != 0:
        file.seek(1, 1)     # Skip the newline character


def render_daily_graph(temperatures, humidity):
    display = Display()
    display().set_pen(Colors.WHITE)

    max_temp = max_temp_hum(temperatures)
    min_temp = min_temp_hum(temperatures)

    max_hum = max_temp_hum(humidity)
    min_hum = min_temp_hum(humidity)

    max_graph = max(max_temp, max_hum)
    min_graph = min(min_temp, min_hum)

    temp_middle = max_temp - (max_temp - min_temp) / 2
    hum_middle = max_hum - (max_hum - min_hum) / 2

    display().text(str(round(max_temp, 1)), 108, 20, 250, 1)
    display().text(str(round(temp_middle, 1)), 108, 60, 250, 1)
    display().text(str(round(min_temp, 1)), 108, 98, 250, 1)

    for i in range(6):
        if temperatures[i] != -404 and temperatures[i + 1] != -404:
            display().line(130 + i * 16, int(temperature_to_pixel(temperatures[i], max_temp, min_temp)),
                           130 + (i + 1) * 16, int(temperature_to_pixel(temperatures[i + 1], max_temp, min_temp)), 2)
            continue

        if temperatures[i] != -404:
            display().pixel(130 + i * 16, int(temperature_to_pixel(temperatures[i], max_temp, min_temp)))

        if temperatures[i + 1] != -404:
            display().pixel(130 + (i + 1) * 16, int(temperature_to_pixel(temperatures[i + 1], max_temp, min_temp)))

    display().update()


def render_weekly_graph(temperatures, humidity):
    display = Display()
    display().set_pen(Colors.WHITE)

    max_temp = max_temp_hum(temperatures)
    min_temp = min_temp_hum(temperatures)

    max_hum = max_temp_hum(humidity)
    min_hum = min_temp_hum(humidity)

    max_graph = max(max_temp, max_hum)
    min_graph = min(min_temp, min_hum)

    temp_middle = max_temp - (max_temp - min_temp) / 2
    hum_middle = max_hum - (max_hum - min_hum) / 2

    display().text(str(round(max_temp, 1)), 108, 20, 250, 1)
    display().text(str(round(temp_middle, 1)), 108, 60, 250, 1)
    display().text(str(round(min_temp, 1)), 108, 98, 250, 1)

    for i in range(3):
        if temperatures[i] != -404 and temperatures[i + 1] != -404:
            display().line(130 + i * 32, int(temperature_to_pixel(temperatures[i], max_temp, min_temp)),
                           130 + (i + 1) * 32, int(temperature_to_pixel(temperatures[i + 1], max_temp, min_temp)), 2)
            continue

        if temperatures[i] != -404:
            display().pixel(130 + i * 32, int(temperature_to_pixel(temperatures[i], max_temp, min_temp)))

        if temperatures[i + 1] != -404:
            display().pixel(130 + (i + 1) * 32, int(temperature_to_pixel(temperatures[i + 1], max_temp, min_temp)))

    display().update()


def temperature_to_pixel(temperature, max_temp, min_temp, pixel_min=20, pixel_max=100):
    """Converts the given temperature to a pixel value between the given pixel range.
    Uses the linear interpolation formula.

    :param temperature: The temperature to convert to a pixel value.
    :param max_temp: The maximum temperature in the given range.
    :param min_temp: The minimum temperature in the given range.
    :param pixel_min: The minimum pixel value in the given range.
    :param pixel_max: The maximum pixel value in the given range.
    :return: The pixel value for the given temperature.
    """

    return pixel_max + ((temperature - min_temp) * (pixel_min - pixel_max)) / (max_temp - min_temp)


def min_temp_hum(values):
    """Returns the minimum value from the given list of values. Ignores the -404 values."""

    min_value = 100

    for value in values:
        if value != -404 and value < min_value:
            min_value = value

    return min_value


def max_temp_hum(values):
    """Returns the maximum value from the given list of values. Ignores the -404 values."""

    max_value = -100

    for value in values:
        if value != -404 and value > max_value:
            max_value = value

    return max_value


def get_measurements(sensor):
    """Returns the measurements for the given sensor from a file.

    :param sensor: The sensor to get the measurements for.
    :return: Two lists containing the temperature and humidity measurements.
    """

    with open("/sensors/measurements/" + sensor.name + "daily.txt", "r") as fr:
        line = fr.readline()
        temp, hum = line.split(";")

    temp = temp.replace("[", "").replace("]", "").split(", ")
    hum = hum.replace("[", "").replace("]", "").split(", ")

    for i in range(len(temp)):
        temp[i] = float(temp[i])
        hum[i] = float(hum[i])

    return temp, hum


if __name__ == "__main__":
    display = Display()

    sensor_manager = sm.SensorManager()
    sensor = sensor_manager.sensors[0]

    # temp, hum = days_data((2024, 2, 15, 3), sensor)
    temp = [22.25736, 23.50342, 23.37879, 22.43661, 24.4356, 20.3456, 23.4464]
    hum = [35.8522, 32.9066, 33.10038, 35.83953, -404, -404, -404]
    # print(temp, hum)

    # render_daily_graph(temp, hum)

    # graph = ContextGraphInterval(ConcreteStrategyDaily())
    # graph.render_graph((2024, 2, 15, 3), sensor, True)
    # print("Graph rendered")
    # graph.render_graph((2024, 2, 15, 3), sensor, False)
    # print("Graph rendered again from memory.")

    graph = ContextGraphInterval(ConcreteStrategyWeekly())
    # graph.render_graph((2024, 2, 15, 3), sensor, True)
    # print("Graph rendered")
    graph.render_graph((2024, 2, 15, 3), sensor, False)
    print("Graph rendered again from memory.")

    utime.sleep(5)
    page_elements.clear_fast()

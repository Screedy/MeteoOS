
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


def get_max_min(temperatures, humidity):
    """Returns the maximum and minimum values from the given lists of temperatures and humidity.

    :param temperatures: The list of temperatures.
    :param humidity: The list of humidity values.
    :return: A tuple containing the maximum and minimum temperature and humidity values.
            In the format (max_temp, min_temp, max_hum, min_hum).
    """

    max_temp = max_temp_hum(temperatures)
    min_temp = min_temp_hum(temperatures)

    max_hum = max_temp_hum(humidity)
    min_hum = min_temp_hum(humidity)

    return max_temp, min_temp, max_hum, min_hum

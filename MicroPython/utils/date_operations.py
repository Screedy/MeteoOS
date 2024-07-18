
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


def start_of_week(day):
    """Returns the start of the week for the given day.

    :param day: The day to reference the week to. Needs to be in a format of a tuple (year, month, day, weekday)
    :return: The start of the week for the given day.
    """

    day_in_week = day[3]

    return day[2] - day_in_week

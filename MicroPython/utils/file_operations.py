from sensors.sensor_manager import SensorManager
from config.sdcard_manager import SDCardManager


def read_n_lines(file, n: int):
    """Reads n lines from the given file. If the file has less than n lines, it will read all the lines.
    Stops the measurements while reading the file to prevent the SD card from crashing.

    :param file: The file to read from.
    :param n: The number of lines to read.
    :return: A list containing the read lines.
    """

    lines = []

    SensorManager().pause_all_measurements()

    for i in range(n):
        line = file.readline()

        if not line:
            break

        lines.append(line)

    SensorManager().resume_measure()
    return lines


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
        file.seek(1, 1)  # Skip the newline character


def file_exists(target_sensor):
    """Checks if the file for the given sensor exists on the SD card.

    :param target_sensor: The sensor to check the file for.
    :return: True if the file exists, False otherwise.
    """

    try:
        sd = SDCardManager()
        sd.mount()
        files = sd.list_files("/sd/measurements")
    except OSError:
        raise OSError("SD card is not mounted")

    if f"{target_sensor.name}.txt" not in files:
        raise OSError(f"File {target_sensor.name}.txt not found on the SD card")

    return True

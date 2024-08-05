import utime
from machine import Pin
from config.config import singleton


class Buttons:
    def __init__(self, pin):
        self._pin = Pin(pin, Pin.IN, Pin.PULL_UP)
        self._last_pressed_time = 0
        self._debounce_time = 300   # ms
        self._debounce = False

    @property
    def pin(self):
        """The pin number of the button."""
        return self._pin

    @pin.setter
    def pin(self, pin):
        if not isinstance(pin, int):
            raise ValueError("Pin must be an integer.")

        if not 0 <= pin <= 30:
            raise ValueError("Pin cannot be less than 0 or greater than 30.")

        self._pin = Pin(pin, Pin.IN, Pin.PULL_UP)

    @property
    def debounce_time(self):
        """The debounce time of the button. Default is 300ms."""
        return self._debounce_time

    @debounce_time.setter
    def debounce_time(self, debounce_time):

        if not isinstance(debounce_time, int):
            raise ValueError("Debounce time must be an integer.")

        self._debounce_time = debounce_time

    def read(self):
        """
        Read the button state. If the button is pressed, return True, else return False.
        If the button is pressed, wait for the debounce time before returning True.

        :return: True if the button is pressed, else False.
        """
        if not self.pin.value():
            if not self._debounce:
                self._debounce = True
                return True
        else:
            self._debounce = False
        return False

    def is_held(self):
        """
        Check if the button is held. If the button is held, return True, else return False.
        If the button is held, wait for the debounce time before returning True again.

        :return: True if the button is held, else False.
        """
        if not self.pin.value():
            current_time = utime.ticks_ms()
            if utime.ticks_diff(current_time, self._last_pressed_time) >= self._debounce_time:
                self._last_pressed_time = current_time
                return True
        return False


button_a = Buttons(12)
button_b = Buttons(13)
button_x = Buttons(14)
button_y = Buttons(15)

if __name__ == "__main__":
    while True:
        """
        if button_a.is_pressed():
            print("Button A is pressed")
        if button_b.is_pressed():
            print("Button B is pressed")
        if button_x.is_pressed():
            print("Button X is pressed")
        if button_y.is_pressed():
            print("Button Y is pressed")
        """

        if button_a.is_held():
            print("Button A is held")
        if button_b.is_held():
            print("Button B is held")
        if button_x.is_held():
            print("Button X is held")
        if button_y.is_held():
            print("Button Y is held")

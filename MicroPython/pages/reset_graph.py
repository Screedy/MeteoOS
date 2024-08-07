from utime import sleep
import uos

from config.config import Display, Colors
from config.buttons import button_a, button_b, button_x, button_y
from graphics import page_elements
from graphics.graphics import draw_confirm, draw_cancel
from utils.file_operations import get_formatted_filenames


def render_reset_graph():
    """Renders the page for resetting the graph."""

    display = Display()

    measurements_list = uos.listdir("/sensors/measurements")
    formatted_list = get_formatted_filenames(measurements_list)
    measurements_list_length = len(measurements_list)
    selected_measurement = 0

    while True:
        sleep(0.1)

        if button_a.is_held():
            selected_measurement = (selected_measurement + 1) % measurements_list_length
        elif button_b.is_held():
            selected_measurement = (selected_measurement - 1) % measurements_list_length
        elif button_x.read():
            uos.remove(f"/sensors/measurements/{measurements_list[selected_measurement]}")
            return True
        elif button_y.read():
            return False

        page_elements.clear_fast()
        display().set_pen(Colors.WHITE)
        page_elements.render_nav_arrows(110)
        display().text(f"Select the measure- ment you want to delete.", 2, 20, 110, 2)
        page_elements.render_items_list(selected_measurement, formatted_list)

        draw_confirm()
        draw_cancel()

        display().update()


if __name__ == "__main__":
    render_reset_graph()

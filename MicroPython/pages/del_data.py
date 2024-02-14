import time
from config.config import *
import page_elements
from config.sdcard_manager import SDCardManager


def render_del_data():
    """Renders the page for deleting data for a specific sensor."""

    display = Display()

    page_elements.clear_fast()

    display().set_pen(Colors.WHITE)
    display().text("Delete data", 2, 0, 236, 2)

    selected_item = 0

    sd = SDCardManager()
    path = "/sd/measurements"
    files = sd.list_files(path)

    while True:
        if button_a.read():
            selected_item = (selected_item + 1) % len(files)
        if button_b.read():
            selected_item = (selected_item - 1) % len(files)
        if button_x.read():
            print(f"Deleting {files[selected_item]}")
            sd.delete_file(f"{path}/{files[selected_item]}")
            files = sd.list_files(path)
            selected_item = 0
        if button_y.read():
            return

        page_elements.clear_fast()
        display().set_pen(Colors.WHITE)
        page_elements.render_nav_arrows(110)
        page_elements.render_items_list(selected_item, files)
        display().update()

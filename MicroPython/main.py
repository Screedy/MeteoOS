from utime import sleep, ticks_diff, ticks_us, localtime
from _thread import start_new_thread
from gc import collect, mem_free


from config.config import Colors, Display, GraphInterval
from config.buttons import button_x, button_y, button_a, button_b
from config.startup import startup
from config.env import env_vars
from graphics import page_elements
import pages.settings as settings
from pages.homepage import render_homepage
from sensors.sensor_manager import SensorManager
from utils.misc_utils import handle_interrupt
import machine


stop_flag = False


def main_task():
    """The main task that runs in the background."""
    global stop_flag
    graph_interval = GraphInterval.Daily
    sensor_manager = SensorManager()

    while not stop_flag:  # Homepage loop
        try:
            if button_x.read():
                if graph_interval is GraphInterval.Daily:
                    graph_interval = GraphInterval.Weekly
                elif graph_interval is GraphInterval.Weekly:
                    graph_interval = GraphInterval.Monthly
                elif graph_interval is GraphInterval.Monthly:
                    graph_interval = GraphInterval.Daily
            elif button_y.read():
                settings.settings_loop()
            elif button_a.is_held():
                sensor_manager.next_sensor()
            elif button_b.is_held():
                sensor_manager.previous_sensor()

            if env_vars['TEST_HOMEPAGE']:
                start = ticks_us()
                render_homepage(graph_interval)
                end = ticks_us()
                diff = ticks_diff(end, start) / 1_000_000

                display = Display()
                page_elements.clear_fast()
                display().set_pen(Colors.RED)
                display().text(f"Render time: {diff:.5f} s", 2, 2, 236, 2)
                display().update()
                sleep(2)
            elif env_vars['TEST_HOMEPAGE_MEMORY']:
                before_gc_collect = mem_free()
                collect()
                start_mem = mem_free()
                end_mem = render_homepage(graph_interval)
                diff_mem = start_mem - end_mem

                display = Display()
                page_elements.clear_fast()
                display().set_pen(Colors.RED)
                display().text(f"Memory before: {start_mem} B", 2, 2, 236, 2)
                display().text(f"Memory after: {end_mem} B", 2, 20, 236, 2)
                display().text(f"Memory diff: {diff_mem} B", 2, 40, 236, 2)
                display().text(f"Bef collect: {before_gc_collect} B", 2, 60, 236, 2)
                display().update()
                sleep(2)
            else:
                render_homepage(graph_interval)

            sleep(0.1)
        except KeyboardInterrupt:
            stop_flag = True  # Set the flag to stop the background task
            sleep(1)  # Allow some time for the background task to notice the flag
            machine.soft_reset()  # Perform a soft reset
            break
        #except Exception as e:
            #print("Error in main_task:", e)


if __name__ == "__main__":
    startup()

    try:
        fr_homepage = open("homepage_settings.txt", "r")
    except OSError:
        fw_homepage = open("homepage_settings.txt", "w")
        fw_homepage.write("0\n0")
        fw_homepage.close()
        fr_homepage = open("homepage_settings.txt", "r")

    last_sensor = int(fr_homepage.readline())
    last_graph_interval = int(fr_homepage.readline())
    fr_homepage.close()

    collect()
    try:
        start_new_thread(handle_interrupt, ())
    except Exception as e:
        print("Error starting main_task thread:", e)

    main_task()

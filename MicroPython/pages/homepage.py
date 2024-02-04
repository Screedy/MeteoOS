from config.config import *
from main import clear_fast, render_homepage, render_settings


def homepage_loop():
    """The homepage loop that runs when homepage is active."""

    try:
        fr_homepage = open("homepage_settings.txt", "r")
    except OSError:
        fw_homepage = open("homepage_settings.txt", "w")
        fw_homepage.write("0\n0")
        fw_homepage.close()
        fr_homepage = open("homepage_settings.txt", "r")

    last_sensor = int(fr_homepage.readline())
    # last_graph_interval = int(fr_homepage.readline())
    fr_homepage.close()

    graph_interval = GraphInterval.Daily
    page = Page.Homepage

    while True:
        if button_x.read():
            # TODO: change the graph interval

            if page is Page.Homepage:
                if graph_interval is GraphInterval.Daily:
                    graph_interval = GraphInterval.Weekly
                elif graph_interval is GraphInterval.Weekly:
                    graph_interval = GraphInterval.Monthly
                elif graph_interval is GraphInterval.Monthly:
                    graph_interval = GraphInterval.Daily

                print("Graph interval changed")
                render_homepage(last_sensor, graph_interval)

        if button_y.read():
            # TODO: go to settings, back etc

            if page is Page.Homepage:
                page = Page.Settings
                print("Settings page opened")
            elif page is Page.Settings:
                page = Page.Homepage
                print("Homepage opened")

        if button_a.read():
            # TODO: change the sensor to previous one
            pass
        if button_b.read():
            # TODO: change the sensor to next one
            pass

        if page is Page.Homepage:
            render_homepage(last_sensor, graph_interval)
        elif page is Page.Settings:
            render_settings()

        time.sleep(0.1)
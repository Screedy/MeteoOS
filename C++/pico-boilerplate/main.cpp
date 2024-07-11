#include "pico/stdlib.h"

#include <string.h>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <stdio.h>

#include "config/config.h"
#include "config/Display.h"
#include "graphics/graphics.h"
#include "graphics/page_elements.h"
#include "sensors/DHT11.h"
#include "sensors/SensorManager.h"
#include "pages/Settings.h"
#include "config/sd_card_manager.h"
#include "config/startup.h"
#include "graphics/qrcode_graphics.h"
#include "rtc.h"
#include "hardware/timer.h"
#include "graphics/graph/strategy_graph_interval.h"
#include "graphics/graph/concrete_strategy_daily.h"
#include "graphics/graph/concrete_strategy_weekly.h"
#include "graphics/graph/context_graph_interval.h"
#include "config/rtc_module.h"

using namespace pimoroni;

void render_homepage(int graph_interval){
    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();

    clear_fast();
    graphics.set_pen(Colors::WHITE);

    render_homepage_buttons(graph_interval);
    render_nav_arrows(6);
    render_sensor_details();

    graphics.line(Point{100, 16}, Point{100, 120});
    graphics.line(Point{101, 16}, Point{101, 120});
    graphics.line(Point{102, 16}, Point{102, 120});

    // If time is set, render the graph
    bool time_set = is_rtc_set();
    if (time_set){
        // Get the current active sensor
        SensorManager& sensor_manager = SensorManager::getInstance();
        std::unique_ptr<Sensor>& active_sensor = sensor_manager.getSensor(sensor_manager.getActiveSensor());

        // Set the strategy for the graph interval
        std::unique_ptr<StrategyGraphInterval> strategy;
        if (graph_interval == GraphInterval::DAILY){
            strategy = std::make_unique<ConcreteStrategyDaily>();
        } else if (graph_interval == GraphInterval::WEEKLY){
            strategy = std::make_unique<ConcreteStrategyWeekly>();
        } else if (graph_interval == GraphInterval::MONTHLY){
            // strategy = std::make_unique<ConcreteStrategyMonthly>();
        }

        if (graph_interval != GraphInterval::MONTHLY){
            ContextGraphInterval setStrategy(std::move(strategy));
            setStrategy.renderGraph(get_current_datetime(), active_sensor.get(), false);
        }
    }

    driver.update(&graphics);
}

/*
 * This is how I tested the SD card functionality for the very first time. Code will stay here for demonstation
 * in my bachelor thesis to directly compare with the MicroPython implementation.
 * This code should be removed but will stay here.
 */
void test_sd(){
    auto& sensor_manager = SensorManager::getInstance();

    sleep_ms(3000);
    printf("Testing SD card\n");

    auto* sd_card_manager = sd_card_manager::get_instance();
    printf("SD card singleton created\n");

    sleep_ms(1000);

    // printf("Mounting SD card\n");
    // sd_card_manager->mount_sd_card();
    // printf("SD card mounted(?)\n");

    sleep_ms(1000);

    auto fr = f_open(&sd_card_manager->get_fil(), "test.txt", FA_WRITE | FA_CREATE_ALWAYS);
    if (fr != FR_OK){
        printf("Failed to open file\n");
        return;
    }
    printf("File opened\n");

    sleep_ms(1000);

    const char* text = "Hello world!";

    if (f_printf(&sd_card_manager->get_fil(), text) < 0){
        printf("Failed to write to file\n");
        return;
    }
    printf("Text written to file\n");

    sleep_ms(1000);

    f_close(&sd_card_manager->get_fil());
    printf("File closed\n");

    sleep_ms(1000);

    sd_card_manager->unmount_sd_card();
    printf("SD card unmounted\n");
}


static void printQr(const qrcodegen::QrCode &qr) {
    int border = 4;
    for (int y = -border; y < qr.getSize() + border; y++) {
        for (int x = -border; x < qr.getSize() + border; x++) {
            std::cout << (qr.getModule(x, y) ? "##" : "  ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//TODO: Delete after testing
bool timer_callback(repeating_timer_t *rt){
    //printf("Timer callback\n");

    if (rt->user_data == nullptr){
        printf("Error: user_data is null\n");
        return false;
    }

    auto* sensor = static_cast<DHT11*>(rt->user_data);

    if (sensor == nullptr){
        printf("Error: sensor is null\n");
        return false;
    }

    try{
        sensor->handle_timer();
    } catch (const std::exception& e){
        printf(" Exception in handle_timer: %s\n", e.what());
        return false;
    } catch (...){
        printf("Unknown exception in handle_timer\n");
        return false;
    }

    printf("Timer callback end\n");
    return true;
}

int main() {
    stdio_init_all();
    //sleep_ms(5000);
    startup();
/*
    repeating_timer_t timer;
    if (!add_repeating_timer_ms(10000, timer_callback, nullptr, &timer)){
        printf("Failed to add timer\n");
    }*/


    Display& display = Display::getInstance();
    auto& driver = display.getDriver();
    auto& graphics = display.getGraphics();
    auto& Buttons = Buttons::getInstance();
    auto& sensor_manager = SensorManager::getInstance();

    // This code is part of the SD card testing done in the function test_sd(). It wont be removed for demonstration
    // purposes.
    /*
    sleep_ms(1000);
    time_init();
    test_sd();
    for(;;){
        sleep_ms(1000);
        printf("SD test loop\n");
    }
    */

    int graph_interval = GraphInterval::DAILY;

    graphics.set_pen(Colors::WHITE);
    graphics.clear();

    auto& sensor1 = sensor_manager.getSensor(0);

    //repeating_timer_t timer;
    //add_repeating_timer_ms(sensor1->getInterval() * 10000, timer_callback, sensor1.get(), &timer);

    #ifdef TEST_BUILD
        int loop_number = 0;
    #endif

    while(true){
        #ifdef TEST_BUILD
            printf("The active sensor is: %s\n", sensor1->getName().c_str());
            printf("Interval: %d\n", sensor1->getInterval());
            printf("Loop number: %d\n", loop_number++);
        #endif
        if (Buttons.is_button_x_pressed()){
            //TODO: change the graph interval
            if (graph_interval == GraphInterval::DAILY){
                graph_interval = GraphInterval::WEEKLY;
            } else if (graph_interval == GraphInterval::WEEKLY){
                graph_interval = GraphInterval::MONTHLY;
            } else if (graph_interval == GraphInterval::MONTHLY){
                graph_interval = GraphInterval::DAILY;
            }
        } else if (Buttons.is_button_y_pressed()){
            printf("Opening menu\n");
            settings_loop();
            printf("Menu closed\n");
        } else if (Buttons.is_button_a_pressed()){
            printf("Button A pressed\n");
            //TODO: Next sensor
        } else if (Buttons.is_button_b_pressed()){
            printf("Button B pressed\n");
            //TODO: Previous sensor
        }

        render_homepage(graph_interval);

        auto err = sensor1->read();
        if (err != 0){
            printf("Error reading sensor\n");
            printf("Error code: %d\n", err);
            continue;
        }
        //printf("Temperature: %f\n", sensor1->getTemperature());
        //printf("Humidity: %f\n", sensor1->getHumidity());
        //printf("Sensor1 temp: %f, hum: %f\n", sensor1->getTemperature(), sensor1->getHumidity());

        sleep_ms(300);
    }

    return 0;
}
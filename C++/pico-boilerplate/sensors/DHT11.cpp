//
// Created by Petr Jurásek on 19.03.2024.
//

#include "DHT11.h"
#include <cstring>
#include <algorithm>

#include "../config/sd_card_manager.h"
#include "../config/rtc_module.h"
#include "../utils/string_modifiers.h"

DHT11::DHT11(unsigned int pin, std::string name, int interval)
    : pin(pin), interval(interval), temperature(0), humidity(0) {

    const char* sensorType = "DHT11";
    this->sensorType = new char[strlen(sensorType) + 1];
    strcpy(this->sensorType, sensorType);

    gpio_init(this->pin);

    last_read = std::chrono::high_resolution_clock::now();

    repeating_timer_t timer;
    this->timer = timer;

    //Copy first 6 characters of the name and add null terminator
    this->name = name.substr(0, 6);
    this->name += '\0';

    if (this->interval > 0) {
        #ifdef TEST_BUILD
            printf("Creating timer for sensor %s.\n", this->name.c_str());
        #endif

        this->write = true;
        // add_repeating_timer_ms(-this->interval * 1000 * 10, timer_callback_dht, (void*) this->name_c, &this->timer);
    } else {
        #ifdef TEST_BUILD
            printf("No timer for sensor %s.\n", this->name.c_str());
        #endif
        this->write = false;
    }

    // cancel_repeating_timer(&this->timer);
}

std::uint8_t DHT11::readByte() {
    std::uint8_t result = 0;
    for (int i = 7; i >= 0; i--){
        waitForChange(1, 50);
        sleep_us(30);
        if (gpio_get(this->pin) == 1){
            result |= (1 << i);
            waitForChange(0, 50);
        }
    }
    return result;
}

int DHT11::read() {

    if (last_read + std::chrono::seconds(interval) > std::chrono::high_resolution_clock::now()) {
        return 0;
    }

    // Send start signal
    gpio_set_dir(this->pin, GPIO_OUT);
    gpio_put(this->pin, 0);
    sleep_ms(20);
    gpio_put(this->pin, 1);
    gpio_set_dir(this->pin, GPIO_IN);
    gpio_pull_up(this->pin);

    // Wait for the sensor to respond
    if (!waitForChange(0, 40)) return 1;
    if (!waitForChange(1, 90)) return 1;
    if (!waitForChange(0, 90)) return 1;

    // Read the data
    std::uint8_t humI = readByte();
    std::uint8_t humF = readByte();
    std::uint8_t tempI = readByte();
    std::uint8_t tempF = readByte();
    std::uint8_t checksum = readByte();

    // Check the checksum
    if (checksum != (humI + humF + tempI + tempF)){
        this->humidity = 0;
        this->temperature = 0;
        return 2;
    }

    // Store the data
    this->humidity = humI + (humF / 100.0F);
    this->temperature = tempI + (tempF / 100.0F);

    write_to_file();

    last_read = std::chrono::high_resolution_clock::now();

    return 0;
}

bool DHT11::waitForChange(bool state, unsigned int timeout_us){
    auto start = time_us_32();
    while (gpio_get(this->pin) != state) {
        if (time_us_32() - start > timeout_us) return false;
        tight_loop_contents();
    }
    return true;
}

float DHT11::getTemperature() {
    return this->temperature;
}

float DHT11::getHumidity() {
    return this->humidity;
}

std::string DHT11::getName() {
    return this->name;
}

SensorType DHT11::getType() {
    return SensorType::DHT11;
}

int DHT11::getPin() {
    return this->pin;
}

char* DHT11::getSensorType() {
    return this->sensorType;
}

int DHT11::getInterval() {
    return this->interval;
}

static bool timer_callback_dht(repeating_timer_t *rt) {
    if(!rt){
        printf("Timer struct pointer is null. Cannot handle timer.\n");
        return false;
    }

    char* sensor_name = (char*) rt->user_data;

    #ifdef TEST_BUILD
        printf("Timer callback for sensor %s.\n", sensor_name);
        return true;
    #endif

    return false;
}

bool DHT11::handle_timer() {
    #ifdef TEST_BUILD
        // printf("Timer callback for sensor %s.\n", this->name.c_str());
    #endif

    // this->read();

    printf("Temperature: %f\n", this->temperature);

    if (this->write) {
        this->write_to_file();
    }

    // Return true to keep the timer running
    return true;
}

void DHT11::write_to_file() {
    FIL fil;
    FRESULT fr;
    sd_card_manager* sd_card_manager = sd_card_manager::get_instance();

    #ifdef TEST_BUILD
        printf("Appending the new measured values to the sensor file.\n");
    #endif

    // Check if time is set
    if (!is_rtc_set()){
        printf("RTC is not set. Cannot write to file.\n");
        return;
    }

    // Create a directory
    auto folder = "0:/measurements";
    fr = f_mkdir(folder);
    if(fr != FR_OK && fr != FR_EXIST){
        printf("Failed to create directory %s\n", folder);
    }

    // Open the file in append mode and write a new line with the measured values
    // The format is: "(yyyy, m, d, dotw, h, m, s, 0);temperature;humidity"
    // File is located in 0:/measurements/sensor_name.txt

    std::string name = this->getName();
    name.erase(std::remove(name.begin(), name.end(), '\0'), name.end());

    std::string path = "0:/measurements/" + name + ".txt\0";

    fr = f_open(&fil, path.c_str(), FA_WRITE | FA_OPEN_APPEND);
    if (fr != FR_OK) {
        printf("Failed to open the file., create it\n");
        fr = f_open(&fil, path.c_str(), FA_WRITE | FA_CREATE_ALWAYS);
        if (fr != FR_OK) {
            printf("Failed to create the file.\n");
            return;
        }
    }

    char buffer[50];
    datetime_t rtc_datetime = get_current_datetime();

    int temperature = (int) this->temperature;
    int humidity = (int) this->humidity;

    sprintf(buffer, "(%04d, %02d, %02d, %02d, %02d, %02d, 0);%d;%d\n",
            rtc_datetime.year, rtc_datetime.month, rtc_datetime.day,
            rtc_datetime.hour, rtc_datetime.min, rtc_datetime.sec,
            temperature, humidity);

    UINT bytes_written;
    fr = f_write(&fil, buffer, strlen(buffer), &bytes_written);
    if (fr != FR_OK) {
        printf("Failed to write to the file.\n");
        f_close(&fil);
        return;
    }

    f_close(&fil);
}

void DHT11::setWrite(bool write) {
    this->write = write;
}

bool DHT11::getWrite() {
    return this->write;
}
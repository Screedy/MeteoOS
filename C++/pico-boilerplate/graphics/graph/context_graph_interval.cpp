//
// Created by Petr Jurásek on 06.07.2024.
//

#include "context_graph_interval.h"

#include "../../config/sd_card_manager.h"
#include "../../utils/measurements_tests.h"

ContextGraphInterval::ContextGraphInterval(std::unique_ptr<StrategyGraphInterval> strategy) : _strategy(std::move(strategy)) {}

void ContextGraphInterval::setStrategy(std::unique_ptr<StrategyGraphInterval> strategy) {
    _strategy = std::move(strategy);
}

void ContextGraphInterval::renderGraph(datetime_t date, Sensor* sensor, bool force_redraw) {

    #ifdef TEST_GRAPH_SPEED
        absolute_time_t start = get_absolute_time();
    #endif

    #ifdef TEST_GRAPH_MEMORY
        if (force_redraw) {
            uint32_t free_memory_before = getFreeHeap();
            printf("Free memory before rendering graph: %d\n", free_memory_before);
        }
    #endif

    // Look if a file for this sensor exists, if not force redraw.
    // The path is 0:/sensors/measurements/"sensor_name"daily.txt (or weekly.txt)
    if (!force_redraw) {
        std::string clean_name = sensor->getName();
        std::string type = "";
        clean_name.erase(std::remove(clean_name.begin(), clean_name.end(), '\0'), clean_name.end());

        std::string file_path = "0:/sensors/measurements/" + clean_name + _strategy->getIntervalName() + ".txt";
        sd_card_manager* sd_card_manager = sd_card_manager::get_instance();


        if (!sd_card_manager->fileExists(file_path)) {
            force_redraw = true;
            #ifdef TEST_BUILD
                printf("File %s does not exist, forcing redraw\n", file_path.c_str());
            #endif

            #ifdef TEST_GRAPH_MEMORY
                uint32_t free_memory_before = getFreeHeap();
                printf("Free memory before rendering graph: %d\n", free_memory_before);
            #endif

        }
    }

    _strategy->renderGraph(date, sensor, force_redraw);

    #ifdef TEST_GRAPH_SPEED
        if (force_redraw) {
            absolute_time_t end = get_absolute_time();
            int64_t elapsed = absolute_time_diff_us(start, end);
            double elapsed_seconds = elapsed / 1000000.0;
            printf("QR code rendering took %f seconds\n", elapsed_seconds);
        }
    #endif

    #ifdef TEST_GRAPH_MEMORY
        if (force_redraw) {
            uint32_t free_memory_after = getFreeHeap();
            printf("Free memory after rendering graph: %d\n", free_memory_after);
        }
    #endif
}
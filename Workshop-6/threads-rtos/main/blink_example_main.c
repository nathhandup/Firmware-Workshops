#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void task1(void *arg)
{
    while (1) {
        printf("Task 1 (HIGH priority) running\n");
        vTaskDelay(pdMS_TO_TICKS(1000));  // yield CPU
    }
}

void task2(void *arg)
{
    while (1) {
        printf("Task 2 (LOW priority) running\n");
        vTaskDelay(pdMS_TO_TICKS(1000));  // yield CPU
    }
}

void app_main(void)
{
    // Create tasks with DIFFERENT priorities
    xTaskCreate(task1, "Task1", 2048, NULL, 2, NULL); // higher priority
    xTaskCreate(task2, "Task2", 2048, NULL, 1, NULL); // lower priority

    // Let them run for 5 seconds
    vTaskDelay(pdMS_TO_TICKS(5000));

    printf("Main done.\n");

    // In ESP-IDF, tasks usually run forever unless deleted
}
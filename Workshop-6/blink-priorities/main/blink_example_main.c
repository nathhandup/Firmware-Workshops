#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"

static const char *TAG = "LOG";

#define BLINK_GPIO 2

static uint8_t s_led_state = 0;

static void blink_led(void)
{
    gpio_set_level(BLINK_GPIO, s_led_state);
}

static void configure_led(void)
{
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

/* 🔹 LOW PRIORITY TASK (priority 0) */
void blink_task(void *arg)
{
    while (1) {
        ESP_LOGI(TAG, "Blink task: LED %s", s_led_state ? "ON" : "OFF");

        blink_led();
        s_led_state = !s_led_state;

        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

/* 🔹 HIGH PRIORITY TASK */
void busy_task(void *arg)
{
    while (1) {
        ESP_LOGI(TAG, "High priority task ACTIVE (blocking blink)");

        /* Stay ready/running briefly */
        vTaskDelay(100 / portTICK_PERIOD_MS);

        ESP_LOGI(TAG, "High priority task BLOCKED");

        /* Block longer → blink runs */
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    configure_led();

    /* 🔹 Create blink task at LOWEST priority */
    xTaskCreate(
        blink_task,
        "blink_task",
        2048,
        NULL,
        0,      // LOWEST priority (idle level)
        NULL
    );

    /* 🔹 Create higher priority task */
    xTaskCreate(
        busy_task,
        "busy_task",
        2048,
        NULL,
        5,      // Higher priority
        NULL
    );
}
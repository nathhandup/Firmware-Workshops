#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
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

/* 🔹 Create a FreeRTOS task */
void blink_task(void *arg)
{
    while (1) {
        ESP_LOGI(TAG, "Turning the LED %s!", s_led_state ? "ON" : "OFF");

        blink_led();

        /* Toggle LED state */
        s_led_state = !s_led_state;

        /* Delay for configured period */
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    configure_led();

    /* 🔹 Create the blink task */
    xTaskCreate(
        blink_task,       // Task function
        "blink_task",     // Task name
        2048,             // Stack size
        NULL,             // Parameter
        5,                // Priority
        NULL              // Task handle TaskHandle_t
    );
}
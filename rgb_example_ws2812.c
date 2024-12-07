#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "led_strip.h"

#define LED_STRIP_GPIO 48  // GPIO pin connected to the WS2812 LED (usually onboard)
#define LED_STRIP_LEN 1    // Number of LEDs in the strip

static led_strip_handle_t led_strip;

void app_main(void) {
    // Configure the LED strip
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_STRIP_GPIO, // GPIO where the WS2812 is connected
        .max_leds = LED_STRIP_LEN,        // Number of LEDs in the strip
    };

    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10 MHz resolution
    };

    // Install the LED strip driver
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));

    // Clear the LED strip (turn off all LEDs)
    ESP_ERROR_CHECK(led_strip_clear(led_strip));
    vTaskDelay(pdMS_TO_TICKS(1000));

    while (1) {
        // Set the LED to red (RGB: 255, 0, 0)
        ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, 0, 255, 0, 0)); // Red
        ESP_ERROR_CHECK(led_strip_refresh(led_strip));
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Set the LED to green (RGB: 0, 255, 0)
        ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, 0, 0, 255, 0)); // Green
        ESP_ERROR_CHECK(led_strip_refresh(led_strip));
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Set the LED to blue (RGB: 0, 0, 255)
        ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, 0, 0, 0, 255)); // Blue
        ESP_ERROR_CHECK(led_strip_refresh(led_strip));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


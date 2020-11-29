#include "sdkconfig.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#define LOW 0
#define HIGH 1
#define ESP32_LED 2
#define BLINK_PERIOD_MS 1000

extern xSemaphoreHandle led_semaphore;

void set_led_low()
{
    gpio_set_level(ESP32_LED, LOW);
}

void set_led_high()
{
    gpio_set_level(ESP32_LED, HIGH);
}

void led_blink_once()
{
    set_led_low();
    vTaskDelay(BLINK_PERIOD_MS / portTICK_PERIOD_MS);
    set_led_high();
    vTaskDelay(BLINK_PERIOD_MS / portTICK_PERIOD_MS);
}

void led_blink_mode()
{
    while (true)
    {
        if (xSemaphoreTake(led_semaphore, portMAX_DELAY))
        {
            led_blink_once();
            xSemaphoreGive(led_semaphore);
        }
    }
}

void led_start()
{
    gpio_pad_select_gpio(ESP32_LED);
    gpio_set_direction(ESP32_LED, GPIO_MODE_OUTPUT);
}

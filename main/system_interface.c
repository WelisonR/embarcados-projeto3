#include <stdio.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"

#include "include/system_interface.h"
#include "include/wifi_interface.h"
#include "include/http_client.h"
#include "include/nvs_manager.h"
#include "include/ipstack_interface.h"
#include "include/openweather_interface.h"
#include "include/led_control.h"

#define MAIN "MAIN"
#define REQUEST_PERIOD_MS 5*60*1000

xSemaphoreHandle wifi_semaphore;
xSemaphoreHandle led_semaphore;

char *http_response;
int http_response_size;
char request_url[256];

void clear_environment_data()
{
  free(http_response);
  http_response_size = 0;
}

void request_weather_data(void *params)
{
  while (true)
  {
    if (xSemaphoreTake(wifi_semaphore, portMAX_DELAY))
    {
      clear_environment_data();
      set_ipstack_url(request_url);
      http_request(request_url);
      struct device_location device_position = get_device_location(http_response);

      clear_environment_data();
      set_openweather_url(request_url, device_position.latitude, device_position.longitude);
      http_request(request_url);
      struct weather_data weather = get_weather_data(http_response);
      display_weather_data(weather);

      led_blink_once();
    }
    xSemaphoreGive(wifi_semaphore);
    vTaskDelay(REQUEST_PERIOD_MS / portTICK_PERIOD_MS);
  }
}

void initialize_system()
{
  initialize_nvs_system();
  led_semaphore = xSemaphoreCreateBinary();
  wifi_semaphore = xSemaphoreCreateBinary();

  clear_environment_data();

  xSemaphoreGive(led_semaphore);
  led_start();
  xTaskCreate(&led_blink_mode, "Controla o acionamento do LED", 4096, NULL, 1, NULL);

  wifi_start();
  xTaskCreate(&request_weather_data, "Recupera informações sobre o clima", 4096, NULL, 1, NULL);
}

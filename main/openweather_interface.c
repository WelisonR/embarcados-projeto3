#include <string.h>
#include "freertos/FreeRTOS.h"
#include "cJSON.h"
#include "include/openweather_interface.h"

#define OPENWEATHER_KEY CONFIG_ESP_OPENWEATHER_KEY

void *set_openweather_url(char *location_url, double latitude, double longitude)
{
    char openweather_base_url[64] = "http://api.openweathermap.org/";
    sprintf(location_url, "%sdata/2.5/weather?lat=%lf&lon=%lf&units=metric&appid=%s",
            openweather_base_url, latitude, longitude, OPENWEATHER_KEY);
    return NULL;
}

struct weather_data get_weather_data(char *openweather_response)
{
    struct weather_data weather;

    cJSON *json = cJSON_Parse(openweather_response);
    cJSON *openweather = cJSON_GetObjectItemCaseSensitive(json, "main");
    weather.current_temperature = cJSON_GetObjectItemCaseSensitive(openweather, "temp")->valuedouble;
    weather.min_temperature = cJSON_GetObjectItemCaseSensitive(openweather, "temp_min")->valuedouble;
    weather.max_temperature = cJSON_GetObjectItemCaseSensitive(openweather, "temp_max")->valuedouble;
    weather.humidity = cJSON_GetObjectItemCaseSensitive(openweather, "humidity")->valuedouble;
    cJSON_Delete(json);

    return weather;
}

void display_weather_data(struct weather_data weather)
{
    printf("\n\n*******************************************\n");
    printf(" - Temperatura atual: %.2lf ºC\n", weather.current_temperature);
    printf(" - Temperatura mínima prevista: %.2lf ºC\n", weather.min_temperature);
    printf(" - Temperatura máxima prevista: %.2lf ºC\n", weather.max_temperature);
    printf(" - Umidade: %.2lf %%\n", weather.humidity);
    printf("*******************************************\n\n");
}

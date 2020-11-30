#include <string.h>
#include "freertos/FreeRTOS.h"
#include "cJSON.h"
#include "include/ipstack_interface.h"

#define IPSTACK_KEY CONFIG_ESP_IPSTACK_KEY

void *set_ipstack_url(char *location_url)
{
    char ipstack_base_url[64] = "http://api.ipstack.com/";
    sprintf(location_url, "%scheck?access_key=%s&fields=latitude,longitude", ipstack_base_url, IPSTACK_KEY);
    return NULL;
}

struct device_location get_device_location(char *ipstack_response)
{
    struct device_location device_position;

    cJSON *json = cJSON_Parse(ipstack_response);
    device_position.latitude = cJSON_GetObjectItemCaseSensitive(json, "latitude")->valuedouble;
    device_position.longitude = cJSON_GetObjectItemCaseSensitive(json, "longitude")->valuedouble;
    cJSON_Delete(json);

    return device_position;
}

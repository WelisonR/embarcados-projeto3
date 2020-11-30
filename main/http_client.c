#include "include/http_client.h"

#include "esp_event.h"
#include "esp_log.h"
#include <string.h>


#define TAG "HTTP"
#define BLOCK_SIZE 2048

extern char *http_response;
extern int http_response_size;

esp_err_t _http_event_handle(esp_http_client_event_t *evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ERROR:
        ESP_LOGI(TAG, "HTTP_EVENT_ERROR");
        break;
    case HTTP_EVENT_ON_CONNECTED:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
        break;
    case HTTP_EVENT_HEADER_SENT:
        ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
        break;
    case HTTP_EVENT_ON_HEADER:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
        break;
    case HTTP_EVENT_ON_DATA:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);

        if (!http_response_size)
        {
            http_response = (char *)malloc(BLOCK_SIZE);
            if (http_response == NULL)
            {
                ESP_LOGE(TAG, "Ocorreu um problema na alocação de memória.");
                return ESP_FAIL;
            }
        }

        memcpy(http_response + http_response_size, evt->data, evt->data_len);
        http_response_size += evt->data_len;
        break;
    case HTTP_EVENT_ON_FINISH:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
        http_response[http_response_size] = '\0';
        break;
    case HTTP_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
        break;
    }

    return ESP_OK;
}

void http_request(char *url)
{
    esp_http_client_config_t request_settings = {
        .url = url,
        .event_handler = _http_event_handle,
    };
    esp_http_client_handle_t client = esp_http_client_init(&request_settings);
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK)
    {
        ESP_LOGI(TAG, "Status = %d, content_length = %d",
                 esp_http_client_get_status_code(client),
                 esp_http_client_get_content_length(client));
    }
    esp_http_client_cleanup(client);
}

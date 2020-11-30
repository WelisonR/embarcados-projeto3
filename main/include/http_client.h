#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "esp_http_client.h"

esp_err_t _http_event_handle(esp_http_client_event_t *evt);
void http_request(char *url);

#endif

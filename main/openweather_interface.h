#ifndef OPENWEATHER_INTERFACE_H
#define OPENWEATHER_INTERFACE_H

struct weather_data {
    double current_temperature;
    double min_temperature;
    double max_temperature;
    double humidity;
};

void *set_openweather_url(char *location_url, double latitude, double longitude);
struct weather_data get_weather_data(char *openweather_response);
void display_weather_data(struct weather_data weather);

#endif /* OPENWEATHER_INTERFACE_H */

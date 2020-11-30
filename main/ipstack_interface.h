#ifndef IPSTACK_INTERFACE_H
#define IPSTACK_INTERFACE_H

struct device_location {
    double latitude;
    double longitude;
};

void *set_ipstack_url(char *location_url);
struct device_location get_device_location(char *ipstack_response);

#endif /* IPSTACK_INTERFACE_H */

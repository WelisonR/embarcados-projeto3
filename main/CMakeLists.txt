set(COMPONENT_SRCS main.c system_interface.c wifi_interface.c http_client.c led_control.c nvs_manager.c ipstack_interface.c openweather_interface.c)
set(COMPONENT_ADD_INCLUDEDIRS "include")

register_component()

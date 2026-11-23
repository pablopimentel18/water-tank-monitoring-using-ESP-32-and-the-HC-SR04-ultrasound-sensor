#ifndef wifi_h
#define wifi_h

#include "freertos/event_groups.h"
#include "esp_event.h"
#include "freertos/FreeRTOS.h"

class WIFI{

    public: 
        WIFI(const char* ssid, const char* password);
    private:
        EventGroupHandle_t wifiEventGroup;
        
        static void eventHandler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

};

#endif 
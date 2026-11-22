#ifndef sensordistancia_h
#define sensordistancia_h

#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_rom_sys.h"

class SensorDistancia {
    public:
        SensorDistancia(gpio_num_t triggerPin, gpio_num_t echoPin);
        float medirDistancia();
    private:
        gpio_num_t triggerPin;
        gpio_num_t echoPin;
};

#endif
#include "SensorDistancia.h"


SensorDistancia::SensorDistancia(gpio_num_t triggerPin, gpio_num_t echoPin) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;

    gpio_reset_pin(triggerPin);
    gpio_reset_pin(echoPin);
    gpio_set_direction(triggerPin, GPIO_MODE_OUTPUT);
    gpio_set_direction(echoPin, GPIO_MODE_INPUT);
}
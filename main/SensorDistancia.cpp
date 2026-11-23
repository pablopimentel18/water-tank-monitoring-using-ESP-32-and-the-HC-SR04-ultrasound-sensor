#include "SensorDistancia.h"
#include "esp_timer.h"
#include "esp_rom_sys.h"
#include <vector>
#include <algorithm>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

SensorDistancia::SensorDistancia(gpio_num_t triggerPin, gpio_num_t echoPin) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;

    gpio_reset_pin(triggerPin);
    gpio_reset_pin(echoPin);
    gpio_set_direction(triggerPin, GPIO_MODE_OUTPUT);
    gpio_set_direction(echoPin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(echoPin, GPIO_PULLDOWN_ONLY);
    gpio_set_level(triggerPin, 0);
}

float SensorDistancia::medirUmaVez(){
    gpio_set_level(triggerPin, 0);
    esp_rom_delay_us(2);
    gpio_set_level(triggerPin, 1);
    esp_rom_delay_us(10);
    gpio_set_level(triggerPin, 0);

    int64_t timeoutStart = esp_timer_get_time();
    while(gpio_get_level(echoPin) == 0){
        int64_t currentTime = esp_timer_get_time();
        if (currentTime - timeoutStart > 30000) { 
            return -1.0; 
        }
    }

    int64_t startTime = esp_timer_get_time();
    while(gpio_get_level(echoPin) == 1){
        int64_t currentTime = esp_timer_get_time();
        if (currentTime - startTime > 30000) { 
            return -1.0; 
        } 
    }
    int64_t endTime = esp_timer_get_time();
    
    return (endTime - startTime) * 0.0343 / 2.0;
}


float SensorDistancia::medirDistancia() {
    std::vector<float> leituras;
    int leiturasValidas = 0;
    int tentativas = 0;
    while (leiturasValidas < 5 && tentativas < 10) {
        float distancia = medirUmaVez();
        if (distancia >= 0) {
            leituras.push_back(distancia);
            leiturasValidas++;
        }
        tentativas++;
        vTaskDelay(pdMS_TO_TICKS(60));
    }

    std::sort(leituras.begin(), leituras.end());
    return leituras.at(2);
}


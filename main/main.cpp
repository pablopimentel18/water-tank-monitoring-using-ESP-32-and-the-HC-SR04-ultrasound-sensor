#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "SensorDistancia.h"


extern "C" void app_main(void){

    SensorDistancia sensor(GPIO_NUM_33, GPIO_NUM_32);

    while (1) {
        float distancia = sensor.medirDistancia();
        if (distancia < 0) {
            printf("Erro ao medir a distância\n");
        } else {
            printf("Distância medida: %.2f cm\n", distancia);
        }
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}



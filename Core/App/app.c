

#include "app.h"

void blink(void *arg) {
  while (1) {
    HAL_GPIO_TogglePin(
        GPIOC, GPIO_PIN_13);  // Alternar el estado del LED conectado a PC13
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void sensors(void *arg) {
  while (1) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
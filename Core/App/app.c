

#include "app.h"

static const char *TAG = "app";

void blink(void *arg) {
  while (1) {
    HAL_GPIO_TogglePin(
        GPIOC, GPIO_PIN_13);  // Alternar el estado del LED conectado a PC13
    LOG_DEBUG(TAG, "From blink task");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void sensors(void *arg) {
  while (1) {
    LOG_INFO(TAG, "From sensors task");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
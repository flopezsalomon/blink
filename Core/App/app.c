

#include "app.h"

static const char *TAG = "app";

uint8_t value;

void blink(void *parameters __attribute__((unused))) {
  while (1) {
    HAL_GPIO_TogglePin(
        GPIOC, GPIO_PIN_13);  // Alternar el estado del LED conectado a PC13
    LOG_DEBUG(TAG, "From blink task");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void sensors(void *parameters __attribute__((unused))) {
  while (1) {
    LOG_INFO(TAG, "From sensors task");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

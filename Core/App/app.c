#include "app.h"

static const char *TAG = "app";
char buffer[128];
void blink(void *parameters __attribute__((unused))) {
  while (1) {
    HAL_GPIO_TogglePin(
        GPIOC, GPIO_PIN_13);  // Alternar el estado del LED conectado a PC13
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}

void sensors(void *parameters __attribute__((unused))) {
  while (1) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void shell(void *parameters __attribute__((unused))) {
  while (1) {
    if (comms_recv_line(buffer, 128) > 0) {
      LOG_INFO(TAG, "Msg from user: %s", buffer);
    }
    memset(buffer, 0, sizeof(buffer));
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
#include "app.h"

static const char *TAG = "app";
char buffer[128];

// Variables globales
QueueHandle_t dataQueue;
SemaphoreHandle_t dataSemaphore;

void blink(void *parameters __attribute__((unused))) {
  dataQueue = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
  dataSemaphore = xSemaphoreCreateBinary();

  if (dataQueue == NULL || dataSemaphore == NULL) {
    LOG_FATAL(TAG, "Error creando cola o semáforo\n");
  }
  while (1) {
    HAL_GPIO_TogglePin(
        GPIOC, GPIO_PIN_13);  // Alternar el estado del LED conectado a PC13
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void sensors(void *parameters __attribute__((unused))) {
  uint32_t adcValue1 = 0;
  uint32_t adcValue2 = 0;

  while (1) {
    if (analog_read(1, &adcValue1) == ADC_READ_SUCCESS) {
      LOG_INFO(TAG, "A0: Enviado %d a la cola\n", adcValue1);
    } else {
      LOG_ERROR(TAG, "Error en lectura adc 0!");
    }

    if (analog_read(2, &adcValue2) == ADC_READ_SUCCESS) {
      LOG_INFO(TAG, "A1: Enviado %d a la cola\n", adcValue2);
    } else {
      LOG_ERROR(TAG, "Error en lectura adc 1!");
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void shell(void *parameters __attribute__((unused))) {
  uint32_t receivedValue;
  while (1) {
    if (comms_recv_line(buffer, 128, '\n') > 0) {
      LOG_INFO(TAG, "Msg from user: %s", buffer);
    }
    memset(buffer, 0, sizeof(buffer));
    if (xSemaphoreTake(dataSemaphore, portMAX_DELAY) == pdTRUE) {
      if (xQueueReceive(dataQueue, &receivedValue, portMAX_DELAY) == pdPASS) {
        LOG_INFO(TAG, "Consumidor: Recibido %d y enviado por UART\n",
                 receivedValue);
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void button(void *parameters __attribute__((unused))) {
  while (1) {
    if (button_check_state()) {
      LOG_DEBUG(TAG, "Boton fue presionado");
    }
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}
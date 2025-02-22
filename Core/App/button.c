#include "button.h"

SemaphoreHandle_t xButtonSemaphore = NULL;

int16_t button_init(void) {
  xButtonSemaphore = xSemaphoreCreateBinary();
  return 1;
}

int16_t button_check_state(void) {
  int16_t ret_value = 0;
  if (xSemaphoreTake(xButtonSemaphore, portMAX_DELAY) == pdTRUE) {
    if ((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET)) {
      ret_value = 1;
      HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
    }
  }
  return ret_value;
}

/**
 * @brief  EXTI line detection callbacks.
 * @param  GPIO_Pin: Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  if (GPIO_Pin == GPIO_PIN_5 &&
      HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET) {
    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
    // Dar el semáforo avisando a la tarea de que se pulsó el botón
    xSemaphoreGiveFromISR(xButtonSemaphore, &xHigherPriorityTaskWoken);

    // Si la tarea que recibió el semáforo es de mayor prioridad,
    // se fuerza un cambio de contexto al salir de la ISR
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
  }
}
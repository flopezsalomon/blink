/**
 * @file  analog_sensors.c
 * @brief Libreria para leer sensores analogos
 * @copyright
 */

#include "analog.h"

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;

uint32_t channelArray[2] = {ADC_CHANNEL_0, ADC_CHANNEL_1};
uint32_t rankArray[2] = {ADC_REGULAR_RANK_1, ADC_REGULAR_RANK_2};
uint32_t tmp_check_flag = ADC_FLAG_EOC;

ADC_HandleTypeDef *adc_handler;
// void analog_init(ADC_HandleTypeDef *hadc) { adc = hadc; }

/**
 * @brief  Lee el valor de un sensor analógico del canal especificado.
 * @param  channel: Índice del canal del ADC a leer (0 a 2, correspondiente a
 * los elementos de channelArray).
 * @param  adc_value: Puntero a la variable donde se almacenará el valor leído
 * del ADC.
 * @retval int16_t:
 *         - ADC_READ_SUCCESS (0): Lectura exitosa.
 *         - ADC_READ_ERROR (-1): Error durante la configuración, inicio o
 * lectura del ADC.
 */

int16_t analog_read(uint8_t adc, uint32_t *adc_value) {
  switch (adc) {
    case 1:
      adc_handler = &hadc1;
      break;

    case 2:
      adc_handler = &hadc2;
      break;

    default:
      break;
  }

  HAL_ADCEx_Calibration_Start(adc_handler);
  if (HAL_ADC_Start(adc_handler) != HAL_OK) {
    return ADC_READ_ERROR;  // Error_Handler();
  }

  do {
    vTaskDelay(pdMS_TO_TICKS(100));

  } while ((adc_handler->Instance->SR & tmp_check_flag) == 0UL);

  if (HAL_ADC_PollForConversion(adc_handler, 1) == HAL_OK) {
    *adc_value = HAL_ADC_GetValue(adc_handler);
    HAL_ADC_Stop(adc_handler);
    return ADC_READ_SUCCESS;
  } else {
    HAL_ADC_Stop(adc_handler);

    return ADC_READ_ERROR;
  }
}

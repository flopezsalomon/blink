/**
 * @file analog.h
 * @brief Libreria para lectura de sensores analogos.
 * @copyright
 */

#ifndef ANALOG_H
#define ANALOG_H

#include <inttypes.h>
#include <stdarg.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "stm32f1xx_hal.h"
#include "task.h"

#define CHANNEL0 0
#define CHANNEL1 1
#define CHANNEL2 2
#define ADC_READ_ERROR (-1)
#define ADC_READ_SUCCESS (0)
#define ADC_MAX_VALUE 4095  // Resolución del ADC (12 bits)
#define V_REF 3.3           // Voltaje de referencia del ADC

void analog_init(ADC_HandleTypeDef *hadc);
int16_t analog_read(uint8_t adc, uint32_t *adc_value);

#endif  // ANALOG_H
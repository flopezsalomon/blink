
/**
 * @file comms.h
 * @brief Manejador de controlador uart *
 * @copyright
 */

#ifndef _COMMS_H
#define _COMMS_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "stm32f1xx_hal.h"
#include "stream_buffer.h"
#include "task.h"

int comms_recv_line(char *buf, int buf_len);
int comms_init(UART_HandleTypeDef *huart);

#endif  //_COMMS_H
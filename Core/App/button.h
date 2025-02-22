#ifndef BUTTON_H
#define BUTTON_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "stm32f1xx_hal.h"
#include "stream_buffer.h"
#include "task.h"

int16_t button_init(void);
int16_t button_check_state(void);
#endif  // BUTTON_H
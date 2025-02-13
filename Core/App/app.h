/**
 * @file app.h
 * @brief Tarea principal y lógica de aplicación.
 *
 * @copyright
 */

#include <stdio.h>

#include "FreeRTOS.h"
#include "stm32f1xx_hal.h"
#include "task.h"

#ifndef _APP_H_
#define _APP_H_

void blink(void *arg);
void sensors(void *arg);

#endif /* _APP_H_ */
/**
 * @file app.h
 * @brief Tarea principal y lógica de aplicación.
 *
 * @copyright
 */

#ifndef _APP_H_
#define _APP_H_

#include <stdio.h>

#include "FreeRTOS.h"
#include "log.h"
#include "stm32f1xx_hal.h"
#include "task.h"

void blink(void *arg);
void sensors(void *arg);

#endif /* _APP_H_ */
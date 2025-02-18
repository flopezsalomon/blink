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
#include "comms.h"
#include "log.h"
#include "queue.h"
#include "semphr.h"
#include "stm32f1xx_hal.h"
#include "task.h"

#define QUEUE_LENGTH 5
#define QUEUE_ITEM_SIZE sizeof(int)

void blink(void *arg);
void sensors(void *arg);
void shell(void *arg);

#endif /* _APP_H_ */
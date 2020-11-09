//
// Created by mayn on 2020/11/9 0009.
//

#ifndef FREERTOS_LOG_H
#define FREERTOS_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

void Str_Printf(char *str, ...);
char *send(UART_HandleTypeDef *huart, char *msg);
char *response(UART_HandleTypeDef *huart);
char *sendResponse(char *msg, char *isOk);

#endif //FREERTOS_LOG_H

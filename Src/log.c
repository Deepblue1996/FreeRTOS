//
// Created by mayn on 2020/11/9 0009.
//

#include "log.h"
#include "string.h"
#include "malloc.h"
#include "stdio.h"
#include "stdarg.h"
#include "usart.h"

void Log(char *str, ...) {
    char pStr[sizeof(str) * 10];
    va_list args;
    int n;

    va_start(args, str);
    n = vsprintf(pStr, str, args);
    va_end(args);

    send(&huart2, pStr);
}

/**
 * 发送数据
 * @param huart
 * @param msg
 * @return
 */
char *send(UART_HandleTypeDef *huart, char *msg) {
    if (strcmp(msg, "") == 0) {
        return "";
    }
    HAL_UART_Transmit(huart, (uint8_t *) msg, strlen(msg), 100);
    /*Receive command and save in "rxBuffer" array with 5s timeout*/
}

/**
 * 接收数据
 * @param huart
 * @return
 */
char *response(UART_HandleTypeDef *huart) {
    char *rxBuffer = malloc(100);
    memset(rxBuffer, 0, 100);
    HAL_UART_Receive(huart, (uint8_t *) rxBuffer, 100, 300);

    char *str = strchr(rxBuffer, ':');

    if (str != NULL) {
        char *rxBufferTemp = malloc(100);
        memset(rxBufferTemp, 0, 100);
        strncpy(rxBufferTemp, str + 1, strlen(str) - 1);

        free(rxBuffer);
        return rxBufferTemp;
    }

    return rxBuffer;
}

char *sendResponse(char *msg, char *isOk) {

    int index = 5;

    char rxBuffer[255];

    while (index > 0) {
        HAL_UART_Transmit(&huart1, (uint8_t *) msg, strlen(msg), 30);
        /*Receive command and save in "rxBuffer" array with 5s timeout*/
        HAL_UART_Receive(&huart1, (uint8_t *) rxBuffer, 255, 30);
        /*Process recived command*/

        if (strstr(rxBuffer, isOk) != 0 || strstr(rxBuffer, "ALREADY CONNECTED") != 0) {
            char *str = strstr(rxBuffer, "\000");
            char *dest = malloc(strlen(str));
            memset(dest, 0, strlen(dest));
            strncpy(dest, str + strlen(msg), strlen(str) - strlen(msg));
            char len = strlen(dest);
            dest[len - 1] = '\0';
            return dest;
        }
        if (strstr(rxBuffer, "ERROR") == 0) {
            return "ERROR";
        }
        index--;
    }
    return "ERROR";
}

#include "serial.h"
#include "common.h"
#include "fsm.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const uint8_t *SERIAL_CMD_STR[] = {"raw", "moving average",
                                          "random noise"};

static UART_HandleTypeDef *serial_huart;
static __serial_filter_t serial_curr_filter;
static uint8_t serial_buff[__SERIAL_BUFF_SIZE];
static __serial_data_history_t serial_data_history;
static _Bool serial_buff_ready;

static __INLINE void serial_data_history_insert(uint16_t data) {
    serial_data_history
        .data[++serial_data_history.idx % __SERIAL_DATA_HISTORY_SIZE] = data;
}

static uint16_t serial_data_moving_avg(void) {
    uint16_t avg = 0;
    size_t i = 0;

    while (i < __SERIAL_DATA_HISTORY_SIZE && serial_data_history.data[i] != 0) {
        avg += serial_data_history.data[i++];
    }

    return ((uint16_t)avg / i);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    serial_buff_ready = TRUE;
}

void serial_init(UART_HandleTypeDef *huart) {
    if (NULL == huart) {
        fsm_update(FSM_EVENT_ERROR); 
        return;
    }

    serial_huart = huart;
    serial_curr_filter = SERIAL_FILTER_NONE;
    bzero(serial_buff, __SERIAL_BUFF_SIZE);
    bzero(&serial_data_history, sizeof(__serial_data_history_t));
    serial_buff_ready = FALSE;
}

void serial_read(void) {
    bzero(serial_buff, __SERIAL_BUFF_SIZE);
    serial_buff_ready = FALSE;
    HAL_UART_Receive_IT(serial_huart, serial_buff, __SERIAL_BUFF_SIZE);
}

_Bool serial_buff_is_ready(void) {
    return serial_buff_ready;
}

void serial_parse_buff(void) {
    _Bool err = TRUE;
    serial_buff_ready = FALSE;

    for (size_t i = 0; i < __SERIAL_CMD_STR_LEN && err != FALSE; ++i) {
        if (!strncmp((char *)serial_buff, (char *)SERIAL_CMD_STR[i],
                     strlen((char *)SERIAL_CMD_STR[i]))) {
            serial_curr_filter = (__serial_filter_t)i;
            err = FALSE;
        }
    }

    if (err) {
        fsm_update(FSM_EVENT_ERROR);
    }
}

void serial_send(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int bufflen = vsnprintf(serial_buff, __SERIAL_BUFF_SIZE, fmt, args);
    if (ERR == bufflen) {
        fsm_update(FSM_EVENT_ERROR);
        return;
    }

    HAL_StatusTypeDef stat = HAL_UART_Transmit(serial_huart, serial_buff,
                                               bufflen, __SERIAL_SEND_TIMEOUT);
    if (HAL_OK != stat) {
        fsm_update(FSM_EVENT_ERROR);
        return;
    }
}

void serial_send_data(uint16_t data) {
    serial_data_history_insert(data);

    switch (serial_curr_filter) {
    case SERIAL_FILTER_MOVING_AVG:
        data = serial_data_moving_avg();
        break;

    case SERIAL_FILTER_RAND_NOISE:
        data ^= ((uint16_t)rand() % 0xffffffff);
        break;

    default:
    case SERIAL_FILTER_NONE:
        break;
    }

    serial_send("%hu\n\r", data);
}

#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "stm32f4xx_hal.h"

#include <stddef.h>
#include <stdint.h>

/**
 * @brief The size of the serial buffer.
 */
#define __SERIAL_BUFF_SIZE ((size_t)0xff)

/**
 * @brief The size of the data sent.
 */
#define __SERIAL_BUFF_SEND_SIZE ((size_t)2)

/**
 * @brief The UART transmit timeout.
 */
#define __SERIAL_SEND_TIMEOUT ((uint32_t)0x3e8)

/**
 * @brief The size of the serial history.
 */
#define __SERIAL_DATA_HISTORY_SIZE ((size_t)0x96)

/**
 * @brief The lenght of the array containing commands strings.
 */
#define __SERIAL_CMD_STR_LEN                                                   \
    (sizeof(SERIAL_CMD_STR) / sizeof(SERIAL_CMD_STR[0]))

/**
 * @brief An enum representing filters.
 */
typedef enum {
    SERIAL_FILTER_NONE,       ///< Raw data
    SERIAL_FILTER_MOVING_AVG, ///< Moving average (150 elements)
    SERIAL_FILTER_RAND_NOISE  ///< Random noise
} __serial_filter_t;

/**
 * @brief A structure representing the last 150 values read by hall sensor.
 */
typedef struct {
    uint16_t data[__SERIAL_DATA_HISTORY_SIZE]; ///< Data history.
    size_t idx;                                ///< Current array position.
} __serial_data_history_t;

/**
 * @brief Receiption callback (needed by `HAL_UART_Receive_IT()`)
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

/**
 * @brief Initialize the serial.
 * @param huart Nucleo's UART handler.
 */
void serial_init(UART_HandleTypeDef *huart);

/**
 * @brief Write something to serial.
 * @param fmt The format string
 * @param ... Additional parameters to be formatted.
void serial_send(const char* fmt, ...);

/**
 * @brief Apply a filter to data and send them to serial.
 * @param data The data to send.
 */
void serial_send_data(uint16_t data);


#endif // __SERIAL_H__

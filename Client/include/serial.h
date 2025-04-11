#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <stddef.h>

/**
 * @brief Initialize the serial module.
 * @param pathname The serial port.
 * @return ERR if an error occur, OK otherwise.
 */
int serial_init(const char *pathname);

/**
 * @brief Send data to serial.
 * @param fmt Format string.
 * @param ... Arguments.
 * @return The size of the sent data, ERR otherwise.
 */
int serial_send(const char *fmt, ...);

/**
 * @brief Read data from serial.
 * @param buff The buffer to fill.
 * @param size The buffer size.
 * @return The size of the read data, ERR otherwise.
 */
int serial_read(char *buff, size_t size);

/**
 * @brief Release all the used resources.
 * @return ERR if an error occur, OK otherwise.
 */
int serial_free(void);

#endif // __SERIAL_H__

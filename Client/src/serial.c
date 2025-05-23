#include "serial.h"
#include "defs.h"
#include "slog.h"

#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

static int serial_fd = {0};

int serial_init(const char *pathname) {
    serial_fd = open(pathname, O_RDWR | O_NOCTTY | O_NDELAY);
    if (ERR == serial_fd) {
        SLOG_ERROR("Unable to open the serial port: %s", strerror(errno));
        return ERR;
    }

    // Configure the serial port
    struct termios options;
    tcgetattr(serial_fd, &options);
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    tcsetattr(serial_fd, TCSANOW, &options);

    return OK;
}

int serial_send(const char *fmt, ...) {
    va_list args;
    char buff[STD_BUFFLEN] = {0};

    va_start(args, fmt);

    int ret = snprintf(buff, STD_BUFFLEN, fmt, args);
    if (ERR == ret) {
        SLOG_ERROR("Unable to write on send buffer: %s", strerror(errno));
        return ERR;
    }

    ret = write(serial_fd, buff, ret);
    if (ERR == ret) {
        SLOG_ERROR("Unable to write to the serial port: %s", strerror(errno));
        return ERR;
    }

    return ret;
}

int serial_read(char *buff, size_t size) {
    if (NULL == buff) {
        return ERR;
    }

    int ret = read(serial_fd, buff, size);
    if (ERR == ret) {
        SLOG_ERROR("Unable to read from the serial port: %s", strerror(errno));
        return ERR;
    }

    return ret;
}

int serial_free(void) {
    int ret = close(serial_fd);
    if (ERR == ret) {
        SLOG_ERROR("Unable to close the serial port: %s", strerror(errno));
        return ERR;
    }

    return OK;
}

#include "defs.h"
#include "slog.h"
#include "serial.h"

#include <stdlib.h>

static const char *LOG_FILE = "/tmp/req.log";

int main(int argc, char *argv[]) {
    if (2 != argc) {
        printf("Usage: client [PORT]\n");
        return EXIT_FAILURE;
    }

    SLOG_INIT(LOG_FILE, LV_ALL);
    int ret = {0};

    ret = serial_init(argv[1]);
    if (ERR == ret) {
        return EXIT_FAILURE;
    }

    while (TRUE) {
        // TODO: main logic
    }

    return EXIT_SUCCESS;
}

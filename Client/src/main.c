#include "cli.h"
#include "defs.h"
#include "serial.h"
#include "slog.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *LOG_FILE = "/tmp/req.log";

int main(int argc, char *argv[]) {
    char buff[STD_BUFFLEN] = {0};
    int ret = {0};
    _Bool running = TRUE;

    if (2 != argc) {
        printf("Usage: client [PORT]\n");
        return EXIT_FAILURE;
    }

    SLOG_INIT(LOG_FILE, LV_ALL);
    ret = serial_init(argv[1]);
    if (ERR == ret) {
        return EXIT_FAILURE;
    }

    while (running) {
        printf("> ");
        if (NULL == fgets(buff, STD_BUFFLEN, stdin)) {
            SLOG_ERROR("An error occured while reading input: %s",
                       strerror(errno));
            return EXIT_FAILURE;
        }
        SLOG_DEBUG("buff: %s", buff);

        ret = cli_parse_str(buff, strlen(buff));
        if (CLI_CMD_QUIT == ret) {
            running = FALSE;
            continue;
        } else if (ERR == ret) {
            printf("ERROR: Unknown command\n");
            continue;
        }

        ret = serial_send(cli_cmd2str((cli_cmd_t)ret));
        if (ERR == ret) {
            SLOG_ERROR("An error occured while sending command");
            return EXIT_FAILURE;
        }

        bzero(buff, STD_BUFFLEN);
    }

    return EXIT_SUCCESS;
}

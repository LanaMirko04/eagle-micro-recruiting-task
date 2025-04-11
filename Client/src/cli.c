#include "cli.h"
#include "defs.h"
#include "slog.h"

#include <string.h>
#include <sys/param.h>

static const char *cli_cmd_str[__CLI_CMD_NUM] = {"raw", "moving average",
                                                 "random noise", "quit"};

int cli_parse_str(const char *buff, size_t size) {
    if (NULL == buff) {
        SLOG_ERROR("Unable to parse the buffer: buffer is NULL");
        return ERR;
    }

    for (size_t i = 0; i < __CLI_CMD_NUM; ++i) {
        if (!strncmp(buff, cli_cmd_str[i], MIN(size, strlen(cli_cmd_str[i])))) {
            return i;
        }
    }

    return ERR;
}

const char *cli_cmd2str(cli_cmd_t cmd) {
    if (__CLI_CMD_NUM == cmd) {
        return NULL;
    }

    return cli_cmd_str[cmd];
}

#ifndef __CLI_H__
#define __CLI_H_

#include <stddef.h>

typedef enum {
    CLI_CMD_RAW,
    CLI_CMD_MOV_AVG,
    CLI_CMD_RAND_NOISE,
    CLI_CMD_QUIT,
    __CLI_CMD_NUM
} cli_cmd_t;

/**
 * @brief Parse a string to search a command.
 * @param buff The buffer to parse.
 * @param size The size of the buffer.
 * @return An enum representing the command, ERR otherwise.
 */
int cli_parse_str(const char *buff, size_t size);

/**
 * @brief Convert commands into strings.
 * @param cmd The command.
 * @return The command string, NULL if an error occurs.
 */
const char *cli_cmd2str(cli_cmd_t cmd);

#endif // __CLI_H_

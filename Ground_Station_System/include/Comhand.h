#ifndef COMMANDS_H
#define COMMANDS_H

#include "include/Types.h"

/**
 * @brief Represents a parsed command with its associated arguments.
 *
 * Stores the result of a parsed input string, containing the identified
 * command and up to two optional arguments.
 */
command_t struct {
    command_id cmd;   /**< The command identifier parsed from input. */
    argument_id arg1; /**< The first argument identifier, if present. */
    argument_id arg2; /**< The second argument identifier, if present. */
};

// used to ensure that the command no larger then 3 bytes  
static_assert(sizeof(command_t) == 3, "command_t should be 3 bytes");

//extern const command_t default_cmd;

#endif
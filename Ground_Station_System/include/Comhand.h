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

/**
 * @brief Maps a command name string to its corresponding command ID.
 *
 * Used as an entry in the command lookup table to resolve string tokens
 * from parsed input into their associated command_id values.
 */
typedef struct {
    const char *name; /**< Null-terminated string name of the command (e.g. "Help", "Run"). */
    command_id id;    /**< The command_id value associated with this command name. */
} command_lookup;

/**
 * @brief Maps an argument name string to its corresponding argument ID.
 *
 * Used as an entry in the argument lookup table to resolve string tokens
 * from parsed input into their associated argument_id values.
 */
typedef struct {
    const char *name; /**< Null-terminated string name of the argument (e.g. "aCore", "CW"). */
    argument_id id;   /**< The argument_id value associated with this argument name. */
} argument_lookup;

/** @brief Global table of all recognized commands, terminated or sized by NUM_COMMANDS. */
extern command_lookup command_table[];

/** @brief Global table of all recognized arguments, terminated or sized by NUM_ARGUMENTS. */
extern argument_lookup argument_table[];

/** @brief The number of entries in command_table. */
extern const int NUM_COMMANDS;

/** @brief The number of entries in argument_table. */
extern const int NUM_ARGUMENTS;

/**
 * @brief Parses a space-delimited command string into a command_t.
 * 
 * Tokenizes and interprets the given input string, populating the provided
 * command_t structure with the parsed command name, arguments, and any
 * other relevant fields.
 * 
 * Input is copied to a 64-byte buffer (truncated at 63 chars); @p input
 * is not modified. Tokens beyond the third are ignored. Emits DEBUG
 * output over Serial.
 * 
 * @param input Null-terminated string containing the raw command input to parse.
 * @param cmd   Pointer to a command_t structure to be populated with parsed data.
 * @return      Returns 0 on success, or a non-zero error code on failure.
 */
int parse_command(const char *input, command_t *cmd);

/**
 * @brief Handles and dispatches a parsed command for execution.
 *
 * Takes a fully populated command_t structure and routes it to the
 * appropriate handler or execution logic based on the command type.
 *
 * @param c Pointer to a command_t structure containing the command to handle.
 */
void commhand(command_t *c );

//extern const command_t default_cmd;

#endif
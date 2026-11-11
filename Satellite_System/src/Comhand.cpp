#include "include/Comhand.h"
#include <string.h>
#include <stdlib.h>

//const command_t default_cmd = { CMD_NONE, ARG_NONE, ARG_NONE };

// will need to be changed once commands are finalized  
const char helpTxt[] = 
"place holder help text \r\n"
"puts like the commands or someting IDK \r\n"
"\r\n";

static direction argToDirection(argument_id arg) {
    if (arg == ARG_CW) return CW;
    return CC; // default to CC
}
// Used to compare raw command input with the avalable tokens
// (Fall 2026 Update) Commands are subject to chnage in Sprint 2
command_lookup command_table[] = {
    {"Run", CMD_RUN},
    {"Stop", CMD_STOP},
    //{"Set", CMD_SET},
    {"Help", CMD_HELP}
};

// Used to compare raw command input with the avalable tokens
// (Fall 2026 Update) Arguments are subject to chnage in Sprint 2
argument_lookup argument_table[] = {
    {"X", ARG_X},
    {"Y", ARG_Y},
    {"Z", ARG_Z},
    {"CC", ARG_CC},
    {"CW", ARG_CW},
};

static bool is_axis(argument_id a) { return a >= ARG_X && a <= ARG_Z; }

// Defined here after the arrays so sizeof() resolves correctly
const int NUM_COMMANDS  = sizeof(command_table)  / sizeof(command_table[0]);
const int NUM_ARGUMENTS = sizeof(argument_table) / sizeof(argument_table[0]);

static command_id find_command(const char *tok) {
    for (int i = 0; i < NUM_COMMANDS; i++)
        if (strcmp(tok, command_table[i].name) == 0)
            return command_table[i].id;
    return CMD_UNKNOWN;
}

static argument_id find_argument(const char *tok) {
    for (int i = 0; i < NUM_ARGUMENTS; i++)
        if (strcmp(tok, argument_table[i].name) == 0)
            return argument_table[i].id;
    return ARG_UNKNOWN;
}

bool read_input(char* buf, size_t buf_size) {
    memset(buf, 0, buf_size);
    int len = Serial.readBytesUntil('\n', buf, buf_size - 1);
    buf[len] = '\0';

    if (len > 0 && buf[len - 1] == '\r')
        buf[--len] = '\0';

    return len > 0;
}


int parse_command(const char *input, command_t *cmd) {
    char buf[64];

    cmd->cmd  = CMD_UNKNOWN;

    for(int i = 0; i < MAX_ARGS; i++) cmd->args[i] = ARG_NONE;

    strncpy(buf, input, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';

    Serial.print("DEBUG raw input: [");
    Serial.print(input);
    Serial.println("]");


    char *saveptr;
    char *token = strtok_r(buf, " ", &saveptr);

    // checks for blank or white space 
    if(token == NULL) return -1;

    // --- Command Parsing ---
    cmd->cmd = find_command(token);
    if (cmd->cmd == CMD_UNKNOWN) {
        Serial.println("DEBUG: no command match found");
        return -1;
    }
    // Grab the next argument while one is available
    int x = 0;
    while((token = strtok_r(NULL, " ", &saveptr)) != NULL) { 
        if(x >= MAX_ARGS) {
            Serial.println("ERROR: too many arguments");
            return -1;
        }
        argument_id id = find_argument(token);

        if (id == ARG_UNKNOWN) {
            Serial.print("ERROR: unknown argument: ");
            Serial.println(token);
            return -1;
        }

        cmd->args[x++] = id;

        Serial.print("DEBUG arg"); Serial.print(x);Serial.print("token: ["); Serial.print(token); Serial.println("]");
        Serial.print("DEBUG arg"); Serial.print(x);Serial.print("id: "); Serial.println((int)cmd->args[x-1]);
    }
    return 0;
}

// (Fall 2026 Update) will need to be changed for Sprint 2, will not work  
/*
void commhand(command_t *c ) {
    switch(c->cmd) {
        
        case CMD_RUN: {
            if (!c->arg1) { 
                Serial.println("ERROR: invalid axis"); 
                break; 
            }
            //Magnetorquer* mag = findMag((int)c->arg1);
            /*
            if (!mag) { 
                Serial.println("ERROR: mag not found"); 
                break;
            }
            
            mag->begin().setTorque(argToDirection(c->arg2));
            
            break;
        }
        /*
        case CMD_STOP: {
            if (c->arg1 == ARG_UNKNOWN) {
                stop_all_mock();
            } else {
                if (!c->arg1) {
                    Serial.println("ERROR: invalid axis");
                    break;
                }
                Magnetorquer* mag = findMag((int)c->arg1);
                if (!mag)  {
                    Serial.println("ERROR: mag not found");
                    break;
                }
                return stop_mock((int)c->arg1);
            }
            break;
        }
        
        case CMD_HELP:
            Serial.println( helpTxt );
            break;

        default:
            break;
    }
}
*/


int commhand_mock(command_t *c){
        
    switch(c->cmd) {
        
        case CMD_RUN: {
            if (!is_axis(c->args[0])) { 
                Serial.println("ERROR: invalid axis"); 
                return -1; 
            }

            if (c->args[1] != ARG_CC && c->args[1] != ARG_CW) {
                    Serial.println("ERROR: invalid direction");
                    return -1;
                }
            return run_wheel_mock((int)c->args[0], argToDirection(c->args[1]));
        }

        case CMD_STOP: {
            if (c->args[0] == ARG_NONE) return stop_all_mock();
            if (!is_axis(c->args[0])) {
                Serial.println("ERROR: invalid axis");
                return -1;
            }
            return stop_mock((int)c->args[0]);
        }

        case CMD_HELP:
            // Fall2026 UPDATE: need to actually add help text that matches with the documentations 
            //Serial.println( helpTxt );
            return 5;

        default:
            return -1;
    }
}

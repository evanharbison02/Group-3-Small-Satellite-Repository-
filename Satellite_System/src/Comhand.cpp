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

// Defined here after the arrays so sizeof() resolves correctly
const int NUM_COMMANDS  = sizeof(command_table)  / sizeof(command_table[0]);
const int NUM_ARGUMENTS = sizeof(argument_table) / sizeof(argument_table[0]);

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
    cmd->arg1 = ARG_UNKNOWN;
    cmd->arg2 = ARG_UNKNOWN;

    strncpy(buf, input, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';

    Serial.print("DEBUG raw input: [");
    Serial.print(input);
    Serial.println("]");


    char *saveptr;
    char *token = strtok_r(buf, " ", &saveptr);

    // --- Command Parsing ---
    for (int i = 0; i < NUM_COMMANDS; i++) {
        if (strcmp(token, command_table[i].name) == 0) {  
            cmd->cmd = command_table[i].id;
            Serial.println("DEBUG: command matched!");
            break;
        }
    }
    if (cmd->cmd == CMD_UNKNOWN) {
        Serial.println("DEBUG: no command match found");
        return -1;
    }
    // subsequent calls:
    token = strtok_r(NULL, " ", &saveptr);
    // -- Arg1 ---
    if (token == NULL) {
        cmd->arg1 = ARG_NONE;
        return 0;
    }
    for (int i = 0; i < NUM_ARGUMENTS; i++) {
        if (strcmp(token, argument_table[i].name) == 0) {
            cmd->arg1 = argument_table[i].id;
            break;
        }
    }
    Serial.print("DEBUG arg1 token: ["); Serial.print(token); Serial.println("]");
    Serial.print("DEBUG arg1 id: ");     Serial.println((int)cmd->arg1);

    // --- Arg2 ---
    token = strtok_r(NULL, " ", &saveptr);
    
    // --- Arg2 ---
    if (token == NULL) {          // ← guard token, not input
        cmd->arg2 = ARG_NONE;
        return 0;
    }
    for (int i = 0; i < NUM_ARGUMENTS; i++) {
        if (strcmp(token, argument_table[i].name) == 0) {
            cmd->arg2 = argument_table[i].id;
            break;
        }
    }
    Serial.print("DEBUG arg2 token: ["); Serial.print(token); Serial.println("]");
    Serial.print("DEBUG arg2 id: ");     Serial.println((int)cmd->arg2);


    return 0;
}

// (Fall 2026 Update) will need to be changed for Sprint 2, will not work  
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
            */
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
        */
        case CMD_HELP:
            Serial.println( helpTxt );
            break;

        default:
            break;
    }
}

int commhand_mock(command_t *c){
        
    switch(c->cmd) {
        
        case CMD_RUN: {
            if (!c->arg1) { 
                Serial.println("ERROR: invalid axis"); 
                break; 
            }
            // need to find a way to add simple check  for input
            /*
            Magnetorquer* mag = findMag((int)c->arg1);
            if (!mag) { 
                Serial.println("ERROR: mag not found"); 
                break;
            }
            */

            return run_wheel_mock((int)c->arg1, argToDirection(c->arg2));
            break;
        }

        case CMD_STOP: {
            if (c->arg1 == ARG_NONE) {
                return stop_all_mock();
            } else {
                if (!c->arg1) {
                    Serial.println("ERROR: invalid axis");
                    break;
                }
                /*
                Magnetorquer* mag = findMag((int)c->arg1);
                if (!mag)  {
                    Serial.println("ERROR: mag not found");
                    break;
                }
                */
               return stop_mock((int)c->arg1);
            }
            break;
        }

        case CMD_HELP:
            // Fall2026 UPDATE: need to actually add help text that matches with the documentations 
            //Serial.println( helpTxt );
            return 5;
            break;

        default:
            break;
    }
}

#ifndef TYPES_H
#define TYPES_H
#include <cstdint>

/*
    uint8_t is a data type with a fixed-width of 8 Bits
    This means that each of the enum identifiers are 8 Bits long 
    compared to normal enums which are 32 bits long, a 75% decrease 

    Quick bit math:  
    Character data types are 1 Byte
    There are 8 Bits in a Byte
    In other words each of the enum identifiers are basicly character 

    Don't worry this gives us enough wiggle room as each enum identifier can have 0 - 255 options 
*/ 

// CMDs and ARGs will be changed when we get to Sprint 2

enum command_id : uint8_t {

    CMD_UNKNOWN,
    CMD_NONE,
    CMD_RUN,
    CMD_STOP,
    CMD_HELP

};

enum armumnet_id : uint8_t {

    ARG_UNKNOWN,
    ARG_NONE,
    ARG_ACORE,
    ARG_SCORE1,
    ARG_SCORE2,
    ARG_CC,
    ARG_CW,

};

// error types 
enum error_id : uint8_t {

    ERR_UNKNOWN,
    ERR_lOGIC,
    ERR_INPUT,

ERR_COUNT
};

// origin of error 
enum origin_id : uint8_t {

    ORIG_UNKNOWN,
    ORIG_COMMHAND,
    ORIG_LOGGER,
    ORIG_POWER,
    // more files will be added later on

ORIG_COUNT
};

// the meseage that will be mapped to the repective error message id 
enum message_id : uint8_t {

    MESS_UNKNOWN,
    MESS_PLACEHOLDER,

MESS_CONT
};

#endif
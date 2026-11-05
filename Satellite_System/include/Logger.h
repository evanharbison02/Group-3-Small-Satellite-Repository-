#ifndef LOGGER_H
#define LOGGER_H

#include "include/Types.h"

typedef struct {
    origin_id file;
    uint8_t error_index;  
}error_t;

extern const char* errer_message_table[ORIG_COUNT][];

extern char* error_type_array[ ERR_COUNT ];

extern char* error_origin_array[ ORIG_COUNT ];

extern char* error_message_array[ MESS_COUNT ];

extern const int NUM_ERRORS;

error_t create_error(origin_id file_location, uint8_t error_index);


#endif

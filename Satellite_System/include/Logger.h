#ifndef LOGGER_H
#define LOGGER_H

#include "include/Types.h"

error_t struct{
    error_id err;
    origin_id file;
    message_id message; 
};

extern char* error_type_array[ ERR_COUNT ];

extern char* error_origin_array[ ORIG_COUNT ];

extern char* error_message_array[ MESS_COUNT ];



#endif

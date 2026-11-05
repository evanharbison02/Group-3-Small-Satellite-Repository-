#include "include/types"
#include "include/Logger.h"
#include <string.h>
#include <stdlib.h>

/*
To-Do need to create mapping tables for each error for each file
in other words, the Comhand files needs it own mapping table

*/
static const char* Comhand[] = {"bullshit"};

static const char* Logger[] = {};

static const char* Power[] = {};

static const char* Radio[] = {};

static const char* LED[] = {};

char errer_message_table[][] = {
    
    {

    },

    {
        
    },
    
    {

    },


}

// determins 
const int NUM_ERRORS = sizeof(errer_message_table[0]) / sizeof(errer_message_table[0][0]);

// change return type later once i get this finalized
void map_error()


// will take the value from the index of the message to map to and the file origin of the error  
error_t create_error(origin_id file_location, uint8_t error_index){
    // place holder return so the compiler dose not yell at me
    // Initialize a new error struct 
    error_t *err_message;

    err_message->file = file_location;
    err_message->error_index = error_index;







    return NULL
}
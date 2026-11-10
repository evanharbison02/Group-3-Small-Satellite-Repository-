#include "include/Types.h"
#include "include/Logger.h"
#include <Arduino.h>
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

char error_origin_array[] = {
    "Comhand.cpp",
    "Logger.cpp",
    "Power.cpp",
    "Led.cpp",
    "Attitude.cpp",
    "Radio.cpp"
}

// determins 
const int NUM_ERRORS = sizeof(errer_message_table[0]) / sizeof(errer_message_table[0][0]);

// change return type later once i get this finalized
void map_error()




// will take the value from the index of the message to map to and the file origin of the error  
error_t create_debug_error(origin_id file_location, uint8_t error_index){
    
    // Initialize a new error struct 
    error_t *err_message;
    // fill in the error message struct so it can be shipped to ground station
    err_message->file = file_location;
    err_message->error_index = error_index;
    
    return err_message;
}

void read_error_mess(error_t err){

    char message_buff[64];
    int file_i = err->file;
    int error_i = err->error_index; 
    message_buff = 

}


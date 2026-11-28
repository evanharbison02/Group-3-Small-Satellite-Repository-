#include "include/Led.h"

// use this to select the number of leds that we have on the satellite 
uint8_t NeoPixel_Pin = 13;
uint8_t num_leds = 4;

Adafruit_NeoPixel NeoPixel(num_leds, NeoPixel_Pin, NEO_GRB + NEO_KHZ800);

void led_setup( void ){
    NeoPixel.begin();
    NeoPixel.show();
}

int led_Safe(int debug){
    if (debug == 1) Serial.println("In Safe mode");
    // place the led order for Safe mode
    return 6;
}

int led_Standby(int debug){
    if (debug == 1) Serial.println("In StandBy mode");
    // place the led order for StandBy mode
    return 7;
}

int led_Science(int debug){
    // place the led order for Science mode
    if (debug == 1) Serial.println("In Science mode");
    // place the led order for Science mode
    return 8;
}

int set_mode(uint8_t mode){
    int debug = 1;
    switch(mode){
        case ARG_SAFE:
            // run safe led order 
            return led_Safe(debug);
        case ARG_STANDBY: 
            // run standby led order 
            return led_Standby(debug);       
        case ARG_SCIENCE: 
            // run Science led order
            return led_Science(debug);
        defult: return -1;

    }    
}

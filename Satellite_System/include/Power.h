#ifndef POWER_H
#define POWER_H

#include "include/Types.h"
#include <Wire.h>
#include <Adafruit_INA219.h>

//#define MAX_BAT_CAP 10200.00f

// change these values based on the pins used on the ESP
extern uint8_t Pin_SDA = 21;
extern uint8_t Pin_SCL = 22; 

// INA219 Measurement Variables 
extern float shuntvoltage;
extern float busvoltage;
extern float current_mA;
extern float loadvoltage;
extern float power_mW;

// Initialize variables for the SoC logic 
extern float SoC;
extern float q_capacity;
extern float q_max;
extern unsigned long last_time;


// Initialize INA219 
extern Adafruit_INA219 ina219;


int set_up_INA219( void );

void take_measurment( int flag );

float get_curr_SoC( void );



#endif
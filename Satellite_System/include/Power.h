#ifndef POWER_H
#define POWER_H

#include "include/Types.h"
#include <Wire.h>
#include <Adafruit_INA219.h>

// change these values based on the pins used on the ESP
const uint8_t Pin_SDA = 21;
const uint8_t Pin_SCL = 22; 

int set_up_INA219(uint8_t SDA_Pin, uint8_t SCL_Pin);

int take_measurment();

float get_curr_SoC();



#endif
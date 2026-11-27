#ifndef LED_H
#define LED_H
#include "include/Types.h"
#include <Adafruit_NeoPixel.h>
#include "string.h"

#define NEOPIXEL_PIN = 13
extern uint8_t num_leds; 

extern Adafruit_NeoPixel NeoPixel;

void led_setup( void );

int led_Safe(int debug);

int led_Standby(int debug);

int led_Science(int debug);

int set_mode(uint8_t mode);

#endif
#ifndef ATTITUDE
#define ATTITUDE

#include "include/Types.h"
#include <Arduino.h>

extern const char* axis_of_three[];

typedef enum {
    CC, /**< Counter-clockwise current direction. */
    CW, /**< Clockwise current direction. */
} direction;


int run_wheel_mock(int axis, direction dir );

int stop_mock(int axis);

int stop_all_mock(void);

#endif
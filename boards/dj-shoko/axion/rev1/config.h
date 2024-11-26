#pragma once

#define ONBOARD_LED 25

#define BUTTON_DRIVER direct
#define BUTTONS_AVAILABLE 12
#define BUTTON_PINS 18, 16, 14, 12, 10, 8, 6, 4, 2, 22, 24
//
#define LIGHT_DRIVER direct
#define LIGHTS_AVAILABLE 12
#define LIGHT_PINS 19, 17, 15, 13, 11, 9, 7, 5, 3, 23, 25

#define ENCODER_DRIVER direct
#define ENCODERS_AVAILABLE 2
#define ENCODER_PINS [0] = {26,27}, [1] = {28,29}

#define RGB_DRIVER pio
#define RGB_CHANNELS_AVAILABLE 2
#define RGB_PINS 0, 1
#define RGB_PIO pio0

/*** Chain Inclusion ***/
#include_next "config.h"

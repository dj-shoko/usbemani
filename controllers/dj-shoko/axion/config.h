#pragma once

/*** Controller Type ***/
#define CONTROLLER_TYPE iidx

/*** Buttons ***/
#define BUTTONS_ACTIVE    11

/*** Encoders ***/
#define ENCODERS_ACTIVE   2
#define ENCODER_PPR       72

/*** RGB ***/
#define RGB_CHANNELS_ACTIVE   1
#define RGB_LED_TYPE          WS2812
#define RGB_LEDS_PER_CHANNEL  144

/*** Chain Inclusion ***/
#include_next "config.h"

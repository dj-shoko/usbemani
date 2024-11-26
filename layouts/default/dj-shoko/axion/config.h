#pragma once
/*** Buttons ***/
// The channels in use.
// For our example, we'll use pins 0-6 for our keys, and pins 7-10 for our E1-E4 buttons.
// USBemani will automatically map these in the order provided, so pin 0 becomes our USB "Button 1", and pin 10 becomes "Button 11".
#define BUTTON_CHANNELS 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

/*** Lights ***/
// Override the number of available lights
#undef  LIGHTS_ACTIVE
#define LIGHTS_ACTIVE  11
#define LIGHT_CHANNELS 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

/*** Encoders ***/
#define ENCODER_CHANNELS_REVERSED
#define ENCODER_CHANNELS                0, 1
#define ENCODER_FREQUENCY               16000
#define ENCODER_SAMPLES_UNTIL_VALID     2
#define ENCODER_DIRECTION_THRESHOLD     1
#define ENCODER_DIRECTION_HOLD_TIMEOUT  200

/*** RGB ***/
#define RGB_CHANNELS          0
#define RGB_FRAMERATE_TARGET  120

/*** USB ***/
#define USB_BUTTONS_ACTIVE      11
#define USB_ENCODER_AXES_ACTIVE 2
#define USB_ENCODER_AXES        USB_Axis_X, USB_Axis_Y
#define USB_LIGHTS_ACTIVE       11
#define USB_RGB_ACTIVE          2

/*** Button Combinations ***/
#define BUTTON_COMBO_ARCH_RESET   0, 1  // Key 1 + 2
#define BUTTON_COMBO_KONAMI_CLOUD 7  // E1

/*** Quirks ***/
#define QUIRK_IIDX_LR2_BUTTON_COMBO 1 // Key 1

/*** Additional Includes ***/
#include "usb_labels.h"

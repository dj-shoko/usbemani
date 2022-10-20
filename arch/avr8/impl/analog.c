#include "analog.h"

volatile _analog_t         _analogs[ANALOG_CHANNELS_ACTIVE];
volatile _analog_digital_t _analogs_digital;

#if defined(ANALOG_DRIVER)
#include INCLUDE_IMPL(analog, ANALOG_DRIVER, c)
#endif
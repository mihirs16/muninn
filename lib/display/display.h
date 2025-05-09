#ifndef DISPLAY_H
#define DISPLAY_H

#include <GxEPD2.h>
#include <GxEPD2_BW.h>

// define pin configuration for the EPD display

#define CS_PIN 5
#define DC_PIN 17
#define RST_PIN 16
#define BUSY_PIN 4

// define the EPD display instance using the GxEPD2 library
extern GxEPD2_BW<
    GxEPD2_420_GDEY042T81, 
    GxEPD2_420_GDEY042T81::HEIGHT
> display;

#endif // DISPLAY_H

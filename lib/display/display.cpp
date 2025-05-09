#include <display.h>

GxEPD2_BW<
    GxEPD2_420_GDEY042T81, 
    GxEPD2_420_GDEY042T81::HEIGHT
> display(
    GxEPD2_420_GDEY042T81(
        SS, // CS=D8
        DC_PIN, // DC=D3
        RST_PIN, // RST=D4
        BUSY_PIN // BUSY=D2
    )
);

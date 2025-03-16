#ifndef _WS2812_H
#define _WS2812_H

#define WS2812_PIN 19

#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

void ws2812_init();
void ws2812_display(uint32_t color);

#endif

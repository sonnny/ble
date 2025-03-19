// ws2812.c
#include "ws2812.h"

int t = 0;
int dir = 0;

static inline void put_pixel(PIO pio, uint sm, uint32_t pixel_grb) {
    pio_sm_put_blocking(pio, sm, pixel_grb << 8u);}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);}

static inline uint32_t urgbw_u32(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            ((uint32_t) (w) << 24) |
            (uint32_t) (b);}

void pattern_off(PIO pio, uint sm, uint len, uint t){
  for (uint i = 0; i < len; ++i) put_pixel(pio, sm, 0);}

void pattern_snakes(PIO pio, uint sm, uint len, uint t) {
    for (uint i = 0; i < len; ++i) {
        uint x = (i + (t >> 1)) % 64;
        if (x < 10)
            put_pixel(pio, sm, urgb_u32(0xff, 0, 0));
        else if (x >= 15 && x < 25)
            put_pixel(pio, sm, urgb_u32(0, 0xff, 0));
        else if (x >= 30 && x < 40)
            put_pixel(pio, sm, urgb_u32(0, 0, 0xff));
        else
            put_pixel(pio, sm, 0);}}
            
void pattern_random(PIO pio, uint sm, uint len, uint t) {
    if (t % 8)
        return;
    for (uint i = 0; i < len; ++i)
        put_pixel(pio, sm, rand());}

void pattern_sparkle(PIO pio, uint sm, uint len, uint t) {
    if (t % 8)
        return;
    for (uint i = 0; i < len; ++i)
        put_pixel(pio, sm, rand() % 16 ? 0 : 0xffffffff);}

void pattern_greys(PIO pio, uint sm, uint len, uint t) {
    uint max = 100; // let's not draw too much current!
    t %= max;
    for (uint i = 0; i < len; ++i) {
        put_pixel(pio, sm, t * 0x10101);
        if (++t >= max) t = 0;}}

void ws2812_init(){
  uint offset = pio_add_program(pio0, &ws2812_program);
  ws2812_program_init(pio0, 0, offset, WS2812_PIN, 800000, true);
  pattern_off(pio0, 0, NUM_PIXELS, t);}

void ws2812_display(char *pattern) {
  dir = (rand() >> 30) & 1 ? 1 : -1;
  for (int i = 0; i < 500; ++i){
    if (strcmp(pattern, "snakes") == 0)        pattern_snakes(pio0, 0, NUM_PIXELS, t);
    else if (strcmp(pattern, "random") == 0)   pattern_random(pio0, 0, NUM_PIXELS, t);
    else if (strcmp(pattern, "sparkles") == 0) pattern_sparkle(pio0, 0, NUM_PIXELS, t);
    else if (strcmp(pattern, "greys") == 0)    pattern_greys(pio0, 0, NUM_PIXELS, t);
    else if (strcmp(pattern, "off") == 0)      pattern_off(pio0, 0, NUM_PIXELS, t);   
    sleep_ms(10);
    t += dir;}}

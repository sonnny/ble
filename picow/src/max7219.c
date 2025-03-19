
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "max7219.h"

const uint8_t CMD_NOOP = 0;
const uint8_t CMD_DIGIT0 = 1; // Goes up to 8, for each line
const uint8_t CMD_DECODEMODE = 9;
const uint8_t CMD_BRIGHTNESS = 10;
const uint8_t CMD_SCANLIMIT = 11;
const uint8_t CMD_SHUTDOWN = 12;
const uint8_t CMD_DISPLAYTEST = 15;

static inline void cs_select() {
    asm volatile("nop \n nop \n nop");
    gpio_put(11, 0);  // Active low
    asm volatile("nop \n nop \n nop");}

static inline void cs_deselect() {
    asm volatile("nop \n nop \n nop");
    gpio_put(11, 1);
    asm volatile("nop \n nop \n nop");}

void write_register(uint8_t reg, uint8_t data) {
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = data;
    cs_select();
    spi_write_blocking(spi1, buf, 2);
    cs_deselect();
    sleep_ms(1);}

void write_register_all(uint8_t reg, uint8_t data) {
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = data;
    cs_select();
    for (int i = 0; i< NUM_MODULES;i++) {
        spi_write_blocking(spi1, buf, 2);}
    cs_deselect();}

void display_num(int32_t num){
    int digit = 0;
    while (num && digit < 8) {
        write_register_all(CMD_DIGIT0 + digit, num % 10);
        num /= 10;
        digit++;}}

void clear(){
    for (int i=0;i<8;i++) {
        write_register_all(CMD_DIGIT0 + i, 0);}}

void init_max7219(){
  spi_init(spi1, 10 * 1000 * 1000);
  gpio_set_function(14, GPIO_FUNC_SPI);
  gpio_set_function(15, GPIO_FUNC_SPI);
  gpio_init(11);
  gpio_set_dir(11, GPIO_OUT);
  gpio_put(11, 1);
  write_register_all(CMD_SHUTDOWN, 0);
  write_register_all(CMD_DISPLAYTEST, 0);
  write_register_all(CMD_SCANLIMIT, 7);
  write_register_all(CMD_DECODEMODE, 255);
  write_register_all(CMD_SHUTDOWN, 1);
  write_register_all(CMD_BRIGHTNESS, 8);
  clear();}
  
void display_max7219(uint16_t limit, uint16_t delay){
  clear();
  for(uint16_t i = 0; i < limit; i++){
    display_num(i);
    sleep_ms(delay);}}

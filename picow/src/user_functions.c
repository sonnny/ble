#include "pico/stdlib.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "pico/cyw43_arch.h"
#include "ws2812.h"
#include "process.h"
#include "user_functions.h"

void init_user_functions() {

  // init pico hardware
  ws2812_init();
  
  // 1st user function
  strcpy(user_functions[0].command_name, "rgb");
  strcpy(user_functions[0].command_help,
         "light up ws2812");
  user_functions[0].user_function = rgb;

  // 2nd user function
  strcpy(user_functions[1].command_name, "blink");
  strcpy(user_functions[1].command_help,
         "blink led");
  user_functions[1].user_function = blink;

} // init_user_functions

void rgb(char tokens[][MAX_STRING_SIZE]) { 
  char color[20];
  strcpy(color, tokens[1]);
  if (strcmp(color, "red") == 0) ws2812_display(0x00100000);
  else if (strcmp(color, "blue") == 0) ws2812_display(0x00001000);
  else if (strcmp(color, "green") == 0) ws2812_display(0x10000000);}
  
void blink(char tokens[][MAX_STRING_SIZE]){
  uint16_t iters = atoi(tokens[1]);
  uint16_t delay = atoi(tokens[2]);

  //printf("blink times %d\n",count);
  for(int i = 0; i < iters; i++){
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(delay);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(delay);}}


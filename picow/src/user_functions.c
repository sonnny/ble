#include "pico/stdlib.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "pico/cyw43_arch.h"
#include "ws2812.h"
#include "process.h"
#include "user_functions.h"
#include "my_pwm.h"

void init_user_functions() {

  // init pico hardware
  ws2812_init();
  init_motor();
  
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
  
  strcpy(user_functions[2].command_name, "blink_rgb");
  strcpy(user_functions[2].command_help,
         "blink rgb");
  user_functions[2].user_function = blink_rgb;
  
  strcpy(user_functions[3].command_name, "motor_speed");
  strcpy(user_functions[3].command_help, "set motor speed");
  user_functions[3].user_function = set_motor_speed;
  
  strcpy(user_functions[4].command_name, "motor_direction");
  strcpy(user_functions[4].command_help, "set motor direction");
  user_functions[4].user_function = set_motor_direction;
    
  //when you add user func change process.c ACTIVE_FUNCTIONS

} // init_user_functions

void rgb(char tokens[][MAX_STRING_SIZE]) { 
  //printf("function rgb\n");
  char color[20];
  strcpy(color, tokens[1]);
  if (strcmp(color, "red") == 0) ws2812_display(0x00FF0000);
  else if (strcmp(color, "blue") == 0) ws2812_display(0x0000FF00);
  else if (strcmp(color, "green") == 0) ws2812_display(0xFF000000);}
  
void blink(char tokens[][MAX_STRING_SIZE]){
  //printf("function blink\n");
  uint16_t iters = atoi(tokens[1]);
  uint16_t delay = atoi(tokens[2]);
  for(int i = 0; i < iters; i++){
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(delay);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(delay);}}

void blink_rgb(char tokens[][MAX_STRING_SIZE]){
  //printf("function blink_rgb\n");
  uint16_t iters = atoi(tokens[1]);
  uint16_t delay = atoi(tokens[2]);
  for(int i=0; i<iters; i++){
    ws2812_display(0x00FF0000);
    sleep_ms(delay);
    ws2812_display(0x0000FF00);
    sleep_ms(delay);
    ws2812_display(0xFF000000);
    sleep_ms(delay);}}
    
void set_motor_speed(char tokens[][MAX_STRING_SIZE]){
  //printf("function set motor speed\n");
  char speed[20];
  strcpy(speed, tokens[1]);
  if (strcmp(speed, "stop") == 0) motor_speed(STOP);
  else if (strcmp(speed, "slow") == 0) motor_speed(SLOW);
  else if (strcmp(speed, "medium") == 0) motor_speed(MEDIUM);
  else if (strcmp(speed, "fast") == 0) motor_speed(FAST);}
  
void set_motor_direction(char tokens[][MAX_STRING_SIZE]){
  //printf("function set motor direction\n");
  char direction[20];
  strcpy(direction, tokens[1]);
  if (strcmp(direction, "forward") == 0) motor_direction(1);
  else if (strcmp(direction, "reverse") == 0) motor_direction(0);}

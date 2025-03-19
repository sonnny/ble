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
#include "ili9341.h"
#include "servo.h"
#include "max7219.h"
#include "opto.h"

struct servo_type servo;

void init_user_functions() {

  // init pico hardware
  ws2812_init();
  init_motor();
  init_ili9341();
  init_servo(&servo, 18, false);
  init_max7219();
  init_opto();
  
  // 1st user function
  strcpy(user_functions[0].command_name, "rgb");
  strcpy(user_functions[0].command_help,
         "rgb patterns");
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
  
  strcpy(user_functions[3].command_name, "motor");
  strcpy(user_functions[3].command_help, "set motor speed or directions");
  user_functions[3].user_function = set_motor;
  
  strcpy(user_functions[4].command_name, "screen");
  strcpy(user_functions[4].command_help, "screen info");
  user_functions[4].user_function = screen;
  
  strcpy(user_functions[5].command_name, "servo");
  strcpy(user_functions[5].command_help, "servo functions");
  user_functions[5].user_function = servo_function;
  
  strcpy(user_functions[6].command_name, "counter");
  strcpy(user_functions[6].command_help, "count up max7219 chip");
  user_functions[6].user_function = max7219;
  
  strcpy(user_functions[7].command_name, "ac");
  strcpy(user_functions[7].command_help, "turn ac on off");
  user_functions[7].user_function = ac;
    
  //when you add user func change process.c ACTIVE_FUNCTIONS

} // init_user_functions

void rgb(char tokens[][MAX_STRING_SIZE]) { 
  char pattern[20];
  strcpy(pattern, tokens[1]);
  ws2812_display(pattern);}
  
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
    
void set_motor(char tokens[][MAX_STRING_SIZE]){
  //printf("function set motor\n");
  char choice[20];
  char dir[20];
  strcpy(choice, tokens[1]);
  if (strcmp(choice, "stop") == 0) motor_speed(STOP);
  else if (strcmp(choice, "slower") == 0) motor_speed(SLOWER);
  else if (strcmp(choice, "slow") == 0) motor_speed(SLOW);
  else if (strcmp(choice, "medium") == 0) motor_speed(MEDIUM);
  else if (strcmp(choice, "fast") == 0) motor_speed(FAST);
  else if (strcmp(choice, "forward") == 0) motor_direction(FORWARD);
  else if (strcmp(choice, "reverse") == 0) motor_direction(REVERSE);}
         
void screen(char tokens[][MAX_STRING_SIZE]){
  char choice[20];
  strcpy(choice, tokens[1]);
  if (strcmp(choice, "help") == 0) screen_help();
  else if (strcmp(choice, "clear") == 0) screen_clear();}
  
void servo_function(char tokens[][MAX_STRING_SIZE]){
  char choice[20];
  strcpy(choice, tokens[1]);
  if (strcmp(choice, "center") == 0) servoPosition(&servo, SERVO_CENTER);
  else if (strcmp(choice, "left") == 0) servoPosition(&servo, SERVO_LEFT);
  else if (strcmp(choice, "right") == 0) servoPosition(&servo, SERVO_RIGHT);}
  
void max7219(char tokens[][MAX_STRING_SIZE]){
  uint16_t iters = atoi(tokens[1]);
  uint16_t delay = atoi(tokens[2]);
  display_max7219(iters, delay);}
  
void ac(char tokens[][MAX_STRING_SIZE]){
  char toggle[20];
  strcpy(toggle, tokens[1]);
  if (strcmp(toggle, "on") == 0) set_opto(1);
  else if (strcmp(toggle, "off") == 0) set_opto(0);}

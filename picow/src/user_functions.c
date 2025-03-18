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

struct servo_type servo;

void init_user_functions() {

  // init pico hardware
  ws2812_init();
  init_motor();
  init_ili9341();
  init_servo(&servo, 18, false);
  
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
  
  strcpy(user_functions[3].command_name, "motor");
  strcpy(user_functions[3].command_help, "set motor speed or directions");
  user_functions[3].user_function = set_motor;
  
  strcpy(user_functions[4].command_name, "screen");
  strcpy(user_functions[4].command_help, "screen info");
  user_functions[4].user_function = screen;
  
  strcpy(user_functions[5].command_name, "servo");
  strcpy(user_functions[5].command_help, "servo functions");
  user_functions[5].user_function = servo_function;
    
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


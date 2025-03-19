// pwm.c
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "my_pwm.h"

uint slice_num;
volatile int speed;
volatile int old_speed;

void on_pwm_wrap(){
  pwm_clear_irq(pwm_gpio_to_slice_num(PWM_OUT));
  if(speed != old_speed){
    old_speed = speed;
    pwm_set_chan_level(slice_num, PWM_CHAN_B, speed);}}

void init_motor(){
  gpio_init(DIRECTION);
  gpio_set_dir(DIRECTION, GPIO_OUT);
  gpio_put(DIRECTION, 1);
  gpio_set_function(PWM_OUT, GPIO_FUNC_PWM);
  slice_num = pwm_gpio_to_slice_num(PWM_OUT);
  pwm_clear_irq(slice_num);
  pwm_set_irq_enabled(slice_num, true);
  irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
  irq_set_enabled(PWM_IRQ_WRAP, true);
  pwm_set_wrap(slice_num, WRAP);
  pwm_set_clkdiv(slice_num, CLKDIV);
  pwm_set_chan_level(slice_num, PWM_CHAN_B, 0);
  pwm_set_mask_enabled(1u << slice_num);
  speed = 0;}
  
void motor_speed(uint16_t s){
  speed = s;}

void motor_direction(uint8_t direction){
  //printf("motor_direction: %d\n",direction);
  gpio_put(DIRECTION, direction);}
  

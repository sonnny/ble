// motor.c

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "servo.h"

extern struct servo_type servo;

uint32_t pwm_set_freq_duty_servo(uint slice_num, uint chan, uint32_t f, int d){
  uint32_t clock = 125000000;
  uint32_t divider16 = clock / f / 4096 + (clock % (f * 4096) != 0);
  if (divider16 / 16 == 0) divider16 = 16;
  uint32_t wrap = clock * 16 / divider16 / f - 1;
  pwm_set_clkdiv_int_frac(slice_num, divider16 / 16, divider16 & 0xF);
  pwm_set_wrap(slice_num, wrap);
  pwm_set_chan_level(slice_num, chan, wrap * d / 100);
  return wrap;}

uint32_t pwm_get_wrap_servo(uint slice_num){
  //valid_params_if(PWM, slice_num >= 0 && slice_num < NUM_PWM_SLICES);
  return pwm_hw->slice[slice_num].top;}

void pwm_set_dutyH(uint slice_num, uint chan, int d){
  pwm_set_chan_level(slice_num, chan, pwm_get_wrap_servo(slice_num) * d / 10000);}

void servoPosition(struct servo_type *s, uint p){
  pwm_set_dutyH(s->slice, s->chan, p * 10 + 250);}

void init_servo(struct servo_type *s, uint gpio, bool invert){
  gpio_set_function(gpio, GPIO_FUNC_PWM);
  s->gpio = gpio;
  s->slice = pwm_gpio_to_slice_num(gpio);
  s->chan = pwm_gpio_to_channel(gpio);
  pwm_set_enabled(s->slice, false);
  s->on = false;
  s->speed = 0;
  s->resolution = pwm_set_freq_duty_servo(s->slice, s->chan, 50, 0);
  pwm_set_dutyH(s->slice, s->chan, 250);
  if (s->chan){
    pwm_set_output_polarity(s->slice, false, invert);}
  else { pwm_set_output_polarity(s->slice, invert, false);}
  s->invert = invert;
  // added servo on
  pwm_set_enabled(s->slice, true);
  s->on = true;
  // set servo middle
  pwm_set_dutyH(s->slice, s->chan, (58 * 10) + 250);}
  
void servoOff(struct servo_type *s){
  pwm_set_enabled(s->slice, false);
  s->on = false;}


  


// pwm.h
#ifndef MY_PWM_H
#define MY_PWM_H

#define PWM_OUT 13
#define DIRECTION 8

#define STOP 0
#define SLOW 250
#define MEDIUM 500
#define FAST 999
#define FORWARD 1
#define REVERSE 0

// pwm frequency = system_clock / (CLKDIV * WRAP)
#define WRAP 1000
#define CLKDIV 125.0f

void init_motor();
void motor_speed(uint16_t s);
void motor_direction(uint8_t direction);

#endif

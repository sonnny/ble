// servo.h
#ifndef SERVO_H
#define SERVO_H

#include "pico/stdlib.h"

#define SERVO_CENTER 58
#define SERVO_LEFT 15
#define SERVO_RIGHT 90

struct servo_type{
  uint gpio;
  uint slice;
  uint chan;
  uint speed;
  uint resolution;
  bool on;
  bool invert;};

void init_servo(struct servo_type *s, uint, bool);
void servoPosition(struct servo_type *s, uint); 

#endif

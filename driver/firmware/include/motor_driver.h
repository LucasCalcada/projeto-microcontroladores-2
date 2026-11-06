#pragma once
#include <pico/types.h>

typedef struct {
  bool reverse;
  uint in1;
  uint in2;
  uint pwm;
} Motor;

typedef struct {
  Motor motorA;
  Motor motorB;
} DualDriver;

void motor_init(Motor config);
void motor_move(Motor motor, int speed);

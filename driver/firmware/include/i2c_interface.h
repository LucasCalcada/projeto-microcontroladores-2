#pragma once

#include <hardware/i2c.h>
#include <omni_movement.h>

typedef struct {
  i2c_inst_t *i2c;
  uint sda;
  uint scl;
  int baudrate;
} I2C_Config;

typedef struct {
  OmnidirMovement movement;
} I2C_Packet;

void interface_init();

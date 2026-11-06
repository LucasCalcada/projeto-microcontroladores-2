#pragma once

#include <motor_driver.h>

typedef struct {
  Motor frontLeft;
  Motor frontRight;
  Motor backLeft;
  Motor backRight;
} OmnidirConfig;

typedef struct {
  float x;
  float y;
} Vector2;

typedef struct {
  Vector2 translation;
  float rotation;
} OmnidirMovement;

void omni_move(OmnidirConfig config, OmnidirMovement movement);

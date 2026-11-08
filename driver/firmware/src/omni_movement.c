#include "motor_driver.h"
#include <omni_movement.h>
#include <robot.h>

float speed = 200.0;

void omni_move(OmnidirMovement movement) {
  float fL =
      movement.translation.y + movement.translation.x + movement.rotation;
  motor_move(omniConfig.frontLeft, fL * speed);

  float fR =
      movement.translation.y - movement.translation.x - movement.rotation;
  motor_move(omniConfig.frontRight, fR * speed);

  float bL =
      movement.translation.y - movement.translation.x + movement.rotation;
  motor_move(omniConfig.backLeft, bL * speed);

  float bR =
      movement.translation.y + movement.translation.x - movement.rotation;
  motor_move(omniConfig.backRight, bR * speed);
}

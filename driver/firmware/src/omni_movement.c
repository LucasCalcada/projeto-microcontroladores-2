#include "motor_driver.h"
#include <omni_movement.h>
#include <robot.h>

void omni_move(OmnidirMovement movement) {
  int fL = movement.translation.y + movement.translation.x + movement.rotation;
  motor_move(omniConfig.frontLeft, fL);

  int fR = movement.translation.y - movement.translation.x - movement.rotation;
  motor_move(omniConfig.frontRight, fR);

  int bL = movement.translation.y - movement.translation.x + movement.rotation;
  motor_move(omniConfig.backLeft, bL);

  int bR = movement.translation.y + movement.translation.x - movement.rotation;
  motor_move(omniConfig.backRight, bR);
}

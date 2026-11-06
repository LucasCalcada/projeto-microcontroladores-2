#include "motor_driver.h"
#include <omni_movement.h>

void omni_move(OmnidirConfig config, OmnidirMovement movement) {
  int fL = movement.translation.y + movement.translation.x + movement.rotation;
  motor_move(config.frontLeft, fL);

  int fR = movement.translation.y - movement.translation.x - movement.rotation;
  motor_move(config.frontRight, fR);

  int bL = movement.translation.y - movement.translation.x + movement.rotation;
  motor_move(config.backLeft, bL);

  int bR = movement.translation.y + movement.translation.x - movement.rotation;
  motor_move(config.backRight, bR);
}

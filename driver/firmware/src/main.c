#include "i2c_interface.h"
#include <motor_driver.h>
#include <pico/platform/common.h>
#include <pico/time.h>
#include <robot.h>

int main() {
  motor_init(m1);
  motor_init(m2);
  motor_init(m3);
  motor_init(m4);

  interface_init();

  while (true) {
    tight_loop_contents();
  }
}

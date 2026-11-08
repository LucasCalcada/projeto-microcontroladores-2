#include "i2c_interface.h"
#include <motor_driver.h>
#include <pico/platform/common.h>
#include <pico/stdio_usb.h>
#include <pico/time.h>
#include <robot.h>
#include <stdio.h>

int main() {
  stdio_usb_init();

  printf("Hello World!\n");

  motor_init(m1);
  motor_init(m2);
  motor_init(m3);
  motor_init(m4);

  printf("Motor setup finished\n");
  interface_init();
  printf("Interace setup finished\n");

  while (true) {
    tight_loop_contents();
    if (command_ready()) {
      OmnidirMovement mov = get_movement();
      omni_move(mov);
      printf("Moving %f %f %f\n", mov.translation.x, mov.translation.y,
             mov.rotation);
    }
  }
}

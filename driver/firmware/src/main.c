#include <motor_driver.h>
#include <pico/time.h>

const Motor m1 = {.in1 = 3, .in2 = 2, .pwm = 1, .reverse = false};
const Motor m2 = {.in1 = 5, .in2 = 6, .pwm = 7, .reverse = false};
const Motor m3 = {.in1 = 10, .in2 = 9, .pwm = 8, .reverse = false};
const Motor m4 = {.in1 = 11, .in2 = 12, .pwm = 13, .reverse = false};

DualDriver d1 = {.motorA = m1, .motorB = m2};
DualDriver d2 = {.motorA = m3, .motorB = m4};

int main() {
  motor_init(d1);
  motor_init(d2);

  motor_move(d1.motorA, 1000);
  motor_move(d1.motorB, 1000);
  motor_move(d2.motorA, 1000);
  motor_move(d2.motorB, 1000);
  sleep_ms(1000);
  motor_move(d1.motorA, -1000);
  motor_move(d1.motorB, -1000);
  motor_move(d2.motorA, -1000);
  motor_move(d2.motorB, -1000);
  sleep_ms(1000);
}

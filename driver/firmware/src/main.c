#include <motor_driver.h>
#include <pico/time.h>

const Motor m1 = {.in1 = 3, .in2 = 2, .pwm = 1, .reverse = false};
const Motor m2 = {.in1 = 5, .in2 = 6, .pwm = 7, .reverse = false};
const Motor m3 = {.in1 = 10, .in2 = 9, .pwm = 8, .reverse = false};
const Motor m4 = {.in1 = 11, .in2 = 12, .pwm = 13, .reverse = false};

int main() {
  motor_init(m1);
  motor_init(m2);
  motor_init(m3);
  motor_init(m4);
}

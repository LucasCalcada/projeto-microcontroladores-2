#include <hardware/gpio.h>
#include <hardware/pwm.h>
#include <hardware/structs/io_bank0.h>
#include <motor_driver.h>

static void single_motor_init(Motor motor) {
  // Initialize direction pins
  gpio_init(motor.in1);
  gpio_set_dir(motor.in1, GPIO_OUT);

  gpio_init(motor.in2);
  gpio_set_dir(motor.in2, GPIO_OUT);

  // Initialize PWM pin
  uint slice = pwm_gpio_to_slice_num(motor.pwm);
  gpio_set_function(motor.pwm, GPIO_FUNC_PWM);

  pwm_config conf = pwm_get_default_config();
  pwm_config_set_clkdiv(&conf, 2.0);
  pwm_config_set_wrap(&conf, 1000);

  pwm_init(slice, &conf, true);
  pwm_set_gpio_level(motor.pwm, 0);
}

void motor_init(DualDriver config) {
  single_motor_init(config.motorA);
  single_motor_init(config.motorB);
}

static void handle_motor_direction(Motor motor, bool fwd) {
  bool in1 = fwd;
  bool in2 = !fwd;

  if (motor.reverse) {
    in1 = !in1;
    in2 = !in2;
  }

  gpio_put(motor.in1, in1);
  gpio_put(motor.in2, in2);
}

void motor_move(Motor motor, int speed) {
  if (speed == 0) {
    gpio_put(motor.in1, true);
    gpio_put(motor.in2, true);
  } else {
    bool fwd = speed > 0;
    handle_motor_direction(motor, fwd);
  }

  pwm_set_gpio_level(motor.pwm, speed);
}

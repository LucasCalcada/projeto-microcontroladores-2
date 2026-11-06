#pragma once

#include <i2c_interface.h>
#include <motor_driver.h>
#include <omni_movement.h>

static const Motor m1 = {.in1 = 3, .in2 = 2, .pwm = 1, .reverse = false};
static const Motor m2 = {.in1 = 5, .in2 = 6, .pwm = 7, .reverse = false};
static const Motor m3 = {.in1 = 10, .in2 = 9, .pwm = 8, .reverse = false};
static const Motor m4 = {.in1 = 11, .in2 = 12, .pwm = 13, .reverse = false};

static OmnidirConfig omniConfig = {
    .frontLeft = m2,
    .frontRight = m1,
    .backLeft = m4,
    .backRight = m3,
};

static I2C_Config i2cConfig = {
    .i2c = i2c1, .sda = 14, .scl = 15, .baudrate = 4e5};

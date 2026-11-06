#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <hardware/structs/io_bank0.h>
#include <pico/i2c_slave.h>

#include <i2c_interface.h>
#include <omni_movement.h>
#include <robot.h>

#define I2C_ADDR 0x10
#define I2C_BUFFER_SIZE sizeof(I2C_Packet)

uint8_t commandBuf[I2C_BUFFER_SIZE];
int commandLen = 0;

static void handle_command_finish() {
  // Parse read command
  I2C_Packet *pkt = (void *)&commandBuf;
  OmnidirMovement movement = pkt->movement;
  omni_move(movement);

  // Reset i2c state
  commandLen = 0;
}

static void i2c_callback(i2c_inst_t *i2c, i2c_slave_event_t event) {
  switch (event) {
  case I2C_SLAVE_RECEIVE:
    commandBuf[commandLen++] = i2c_read_byte_raw(i2c);
    break;

  case I2C_SLAVE_REQUEST:
    break;

  case I2C_SLAVE_FINISH:
    handle_command_finish();
    break;
  }
}

void interface_init() {
  gpio_set_function(i2cConfig.sda, GPIO_FUNC_I2C);
  gpio_set_function(i2cConfig.scl, GPIO_FUNC_I2C);

  gpio_pull_up(i2cConfig.sda);
  gpio_pull_up(i2cConfig.scl);

  i2c_init(i2cConfig.i2c, i2cConfig.baudrate);
  i2c_slave_init(i2cConfig.i2c, I2C_ADDR, i2c_callback);
}

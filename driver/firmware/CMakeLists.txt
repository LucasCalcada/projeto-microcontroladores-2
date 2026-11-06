cmake_minimum_required(VERSION 3.18)

set(PICO_BOARD pico_w)
set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/pico-sdk)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

add_compile_options(
  -Wall
  -Wno-format
  -Wextra
  -O3
)

project(proj-semestral-2 C CXX ASM)

pico_sdk_init()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(proj-semestral-2
  src/main.c
  src/motor_driver.c
  src/omni_movement.c
  src/i2c_interface.c
)

target_include_directories(proj-semestral-2 PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(proj-semestral-2
  pico_stdlib
  hardware_pwm
  hardware_gpio
  hardware_i2c
  pico_i2c_slave
)

pico_enable_stdio_usb(proj-semestral-2 1)
pico_enable_stdio_uart(proj-semestral-2 0)

pico_add_extra_outputs(proj-semestral-2)

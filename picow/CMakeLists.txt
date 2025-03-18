cmake_minimum_required(VERSION 3.13)
set(PICO_SDK_PATH "/home/sonny/pico/pico-sdk")

include("${PICO_SDK_PATH}/external/pico_sdk_import.cmake")

project(template C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_library(template
  src/ws2812.c
  src/process.c
  src/user_functions.c
  src/ble.c
  src/ili9341.c
  src/servo.c
  src/gfx.c
  src/my_pwm.c)

target_include_directories(template PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include )
target_include_directories(template PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src )

pico_btstack_make_gatt_header(template PRIVATE "${CMAKE_CURRENT_LIST_DIR}/mygatt.gatt")
pico_generate_pio_header(template ${CMAKE_CURRENT_LIST_DIR}/include/ws2812.pio)

target_link_libraries(template
  hardware_gpio
  hardware_clocks
  hardware_spi
  hardware_dma
  hardware_pwm
  hardware_irq
  pico_btstack_ble
  pico_btstack_cyw43
  pico_cyw43_arch_none
  pico_stdlib)

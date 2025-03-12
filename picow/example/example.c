// example.c
// use nrf connect to test
// send only less the 20 char on ble
// needs to change mtu to send more than 20

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "ble.h"
#include "pico/cyw43_arch.h"
#include "process.h"
#include "ws2812.h"

void main(void){
  struct bt_type ble_data;
  char new_string[80];
  char previous_string[80];

  stdio_init_all();
  ws2812_init();
  ws2812_display(0x00000000); 
  sleep_ms(2000); // do not remove this delay
  multicore_launch_core1(bt_main);
  sleep_ms(1000); // do not remove this delay
  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN,1);
  printf("starting...\n");
  for(;;){
    sleep_ms(100);
    bt_get_latest(&ble_data);
    for(int i = 0; i < ble_data.length; i++) new_string[i] = (char)ble_data.packet[i];
    new_string[ble_data.length] = '\0';
    if (strcmp(new_string, previous_string) != 0){ 
      process_string(new_string);
      strcpy(previous_string, new_string);}}}

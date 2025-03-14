// example.c
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "ble.h"
#include "process.h"

void main(void){
  struct bt_type ble_data;
  char new_string[80];
  char previous_string[80];

  stdio_init_all();
  sleep_ms(2000); // do not remove this delay
  multicore_launch_core1(bt_main);
  sleep_ms(1000); // do not remove this delay
  process_init();
  printf("starting...\n");
  for(;;){
    sleep_ms(1000);
    bt_get_latest(&ble_data);
    for(int i = 0; i < ble_data.length; i++) new_string[i] = (char)ble_data.packet[i];
    new_string[ble_data.length] = '\0';
    //if (strcmp(new_string, previous_string) != 0){
    //printf("new string %s\n",new_string);
    //printf("new length %d\n",strlen(new_string));
    //printf("prev string %s\n",previous_string);
    //printf("prev length %d\n",strlen(previous_string));  
      process_string(new_string);}}
      
     // for(int i=0; i<strlen(new_string); i++) previous_string[i] = (char)new_string[i];
       //  previous_string[strlen(new_string)+1] = '\0'; }}}
      //strncpy(previous_string, new_string, strlen(new_string));}}}


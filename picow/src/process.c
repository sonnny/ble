// process.c

#include <stdio.h>
#include <string.h>
#include "ws2812.h"

void process_string(char *str){
  if (strcmp(str, "rgb red") == 0)        ws2812_display(0x00100000);
  else if (strcmp(str, "rgb blue") == 0)  ws2812_display(0x00001000); 
  else if (strcmp(str, "rgb green") == 0) ws2812_display(0x10000000);   
} 

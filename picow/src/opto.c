
#include "pico/stdlib.h"
#include "opto.h"

void init_opto(){
  gpio_init(22);
  gpio_set_dir(22, GPIO_OUT);
  gpio_put(22, 0);}
  
void set_opto(uint toggle){
  if (toggle == 1) gpio_put(22, 1);
  else gpio_put(22, 0);}

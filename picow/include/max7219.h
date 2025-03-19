#ifndef MAX7219_H
#define MAX7219_H

#define NUM_MODULES 1

void init_max7219();
void display_max7219(uint16_t limit, uint16_t delay);
#endif

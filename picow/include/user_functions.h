#ifndef USER_FUNCS_H
#define USER_FUNCS_H

#define NUMBER_OF_STRING 10
#define MAX_STRING_SIZE 25
#define MAX_USER_FUNCTIONS 10

typedef void (*user_func)(char tokens[][MAX_STRING_SIZE]);

typedef struct usr_funcs {
  char command_name[20];
  char command_help[80];
  user_func user_function; } usr_funcs;
  
extern usr_funcs user_functions[MAX_USER_FUNCTIONS];
  
void init_user_functions();

void rgb(char tokens[][MAX_STRING_SIZE]);
void blink(char tokens[][MAX_STRING_SIZE]);
void blink_rgb(char tokens[][MAX_STRING_SIZE]);
void set_motor(char tokens[][MAX_STRING_SIZE]);
void screen(char tokens[][MAX_STRING_SIZE]);
void servo_function(char tokens[][MAX_STRING_SIZE]);
void max7219(char tokens[][MAX_STRING_SIZE]);

#endif

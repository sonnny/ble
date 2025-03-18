// process.c

#include <stdio.h>
#include <string.h>
#include "user_functions.h"
#include "ili9341.h"

#define NUMBER_OF_STRING 10
#define MAX_STRING_SIZE 25
#define ACTIVE_FUNCTIONS 6 // change to how many active functions

usr_funcs user_functions[MAX_USER_FUNCTIONS];
char tokens[NUMBER_OF_STRING][MAX_STRING_SIZE];

int parse_string(char *str, char tokens[][MAX_STRING_SIZE], char *delim){
  char *buffer = str;
  int x = 0;
  char *token = strtok(buffer, delim);
  while (token != NULL){
    strcpy(tokens[x], token);
    token = strtok(NULL, " ");
    x++;}
    return x;}

void process_init(){
  init_user_functions();}

void process_string(char *str){
  //printf("process string %s\n", str);
  GFX_setTextColor(ILI9341_WHITE);
  GFX_setCursor(0, 200);
  GFX_printf(str);
  GFX_flush();
  int token_cnt = parse_string(str, tokens, " ");

  for (int i = 0; i < ACTIVE_FUNCTIONS; i++){
    if (strcmp(user_functions[i].command_name, tokens[0]) == 0){
      user_functions[i].user_function(tokens);
      break;}}}

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>

#include "linked_list.h"

#define MAX_INPUT_LENGTH 500

char *prompt_and_accept_input();
char *pstat();
int create_process();
void flush_string();

char *prompt_and_accept_input() {
  char *input_buffer = malloc(sizeof(char) * MAX_INPUT_LENGTH);

  printf("Pman: >");

  // write up to MAX_INPUT_LENGTH-1 chars into input_buffer
  fgets(input_buffer, MAX_INPUT_LENGTH, stdin);
  input_buffer[strlen(input_buffer)-1] = '\0';

  return input_buffer;
}

int create_process(char **args) {
  int pid = fork();
  if(pid  < 0) {
    printf("Fork failed");
    return -1;
  }
  else if(pid > 0) {
    return pid;
  }
  else {
    execvp(*args, args);
  }
}

char *pstat(char *pid) {
  return "";
}

// iterate through string char by char
// if not space, append to buffer
// if char is space, ignore. if buffer has something in it, add that to command array and empty the buffer
//assumes NULL-terminated input string
char **parse_input(char *input) {
  int input_len = strlen(input);
  int buffer_len = strlen(input);
  char *buffer = malloc(sizeof(char)*buffer_len+1); // +1 is for \0
  flush_string(buffer, buffer_len+1);

  char **cmd_array = malloc(sizeof(char*)*strlen(input));
  int cmd_index = 0;

  int i;
  for(i = 0; i < input_len; i++) {
    char curr_char = input[i];
    if(isspace(curr_char)) {
      if(strlen(buffer) > 0) {
        char *new_cmd = malloc(sizeof(char)*strlen(buffer)+1); // allocate space for new cmd
        flush_string(new_cmd, strlen(buffer)+1);
        strcpy(new_cmd, buffer);
        cmd_array[cmd_index++] = new_cmd; // add command to array
        flush_string(buffer, buffer_len + 1);
      }
    }
    else {
      char curr_char_str[] = {curr_char, '\0'};
      strncat(buffer, curr_char_str, 1);
    }
  }

  if(strlen(buffer) > 0) {
    printf("adding %s to cmd\n", buffer);
    cmd_array[cmd_index] = buffer;
  }

  return cmd_array;
}

void flush_string(char *str, int len) {
  int i = 0;
  while(i < len) *(str + i++) = '\0';
}

void print_ary(char **ary) {
  int i;
  for(i = 0; ary[i]; i++) printf("%s\n", ary[i]);
}

void free_ary(char **ary) {
  int i;
  for(i = 0; ary[i]; i++) free(ary[i]);
  free(ary);
}

int main(int argc, char **argv) {
  /* /1* char *args[] = {"./inf", "1", "2"}; *1/ */
  /* /1* char *args[] = {"./print1"}; *1/ */
  /* /1* int pid = create_process("./inf", args); *1/ */
  /* int pid = create_process(args); */
  /* sleep(5); */
  /* kill(pid, 15); */
  while(1) {
    char *input;
    input = prompt_and_accept_input();
    char **cmd_array = parse_input(input);
    print_ary(cmd_array);
    free_ary(cmd_array);
    free(input);
  }
}

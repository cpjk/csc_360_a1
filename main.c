#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define MAX_INPUT_LENGTH 500

char *prompt_and_accept_input();
char *pstat();
int create_process();

char *prompt_and_accept_input() {
  char *input_buffer = malloc(sizeof(char) * MAX_INPUT_LENGTH);

  printf("Pman: >");

  // space required before format specifier in order to eat \n left in input buffer
  // from the previous input
  scanf(" %500[^\n]", input_buffer);

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
    printf(input);
    free(input);
    printf("\n");
  }
}

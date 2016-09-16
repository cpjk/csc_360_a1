#include <stdlib.h>
#include <stdio.h>

#define MAX_INPUT_LENGTH 500

char* prompt_and_accept_input() {
  char *input_buffer = malloc(sizeof(char) * MAX_INPUT_LENGTH);

  printf("Pman: >");

  // space required before format specifier in order to eat \n left in input buffer
  scanf(" %500[^\n]", input_buffer);

  return input_buffer;
}

int main(int argc, char **argv) {
  char *input;
  while(1) {
    input = prompt_and_accept_input();
    printf(input);
    printf("\n");
  }
}

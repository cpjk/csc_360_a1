#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/wait.h>

#include "linked_list.h"

#define MAX_INPUT_LENGTH 500

const char *CMDS[] = {"bg", "bglist", "bgkill", "bgstop", "bgstart", "pstat"};
const unsigned int NUM_CMDS = 6;

char *prompt_and_accept_input();
char *pstat();
int create_process();
void flush_string();
void bgkill();
void bglist();
int bgstop();
int bgstart();

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
    printf("Fork for %s failed.\n", args[0]);
    return -1;
  }
  else if(pid > 0) { // in parent
    return pid;
  }
  else {
    errno = 0; // clear errno so errors will be noticed
    if(execvp(*args, args) < 0) { // execute child program
      printf("there was an error executing %s\n", args[0]);
      exit(errno);
    }
  }
}

char *pstat(char *pid) {
  return "";
}

void flush_string_ary(char **ary, int len) {
  int i;
  for(i = 0; i < len; i++) { ary[i] = 0; };
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

  // there could be MAX_INPUT_LENGTH commands that are each one letter in length
  char **cmd_ary = malloc(sizeof(char*)*MAX_INPUT_LENGTH);
  flush_string_ary(cmd_ary, MAX_INPUT_LENGTH);
  int cmd_index = 0;

  int i;
  for(i = 0; i < input_len; i++) {
    char curr_char = input[i];
    if(isspace(curr_char)) {
      if(strlen(buffer) > 0) {
        char *new_cmd = malloc(sizeof(char)*strlen(buffer)+1); // allocate space for new cmd
        flush_string(new_cmd, strlen(buffer)+1);
        strcpy(new_cmd, buffer);
        cmd_ary[cmd_index++] = new_cmd; // add command to array
        flush_string(buffer, buffer_len + 1);
      }
    }
    else {
      char curr_char_str[] = {curr_char, '\0'};
      strncat(buffer, curr_char_str, 1);
    }
  }

  if(strlen(buffer) > 0) { // there is input left in the buffer after the last whitespace character
    char *new_cmd = malloc(sizeof(char)*strlen(buffer)+1); // allocate space for new cmd
    flush_string(new_cmd, strlen(buffer)+1);
    strcpy(new_cmd, buffer);
    cmd_ary[cmd_index] = new_cmd;
  }

  free(buffer);
  return cmd_ary;
}

void flush_string(char *str, int len) {
  int i = 0;
  while(i < len) *(str + i++) = '\0';
}

void print_ary(char **ary) {
  int i;
  for(i = 0; ary[i]; i++) printf("%s\n", ary[i]);
}

void free_ary(char **ary, int ary_len) {
  int i;
  for(i = 0; i < ary_len; i++) {
    if(ary[i]) { free(ary[i]); }
  }
  free(ary);
}

// start a background process with the args given in cmd_ary
// add the process' info to proc_list
int bg(char **cmd_ary, Node *proc_list) {
  if(!cmd_ary[1]) { // no argument was passed to Pman after "bg"
    printf("Too few arguments to bg.\n");
    return -1;
  }

  char **cmd_args = malloc(sizeof(char*)*MAX_INPUT_LENGTH);
  flush_string_ary(cmd_args, MAX_INPUT_LENGTH);

  int i = 1;
  for(i; cmd_ary[i]; i++) {
    char *arg = malloc(sizeof(char)*strlen(cmd_ary[i])+1); // allocate space for new cmd
    flush_string(arg, strlen(cmd_ary[i])+1);
    strcpy(arg, cmd_ary[i]);
    cmd_args[i-1] = arg; // add command to array
  }

  int pid = create_process(cmd_args);
  if(pid < 0) { // error creating background process
    free_ary(cmd_args, MAX_INPUT_LENGTH);
    printf("no background process was created\n");
    return -1;
  }
  printf("creating new node\n");
  fflush(stdout);
  Node *new_node = create_node(pid);
  set_node_name(new_node, *cmd_args);
  set_node_status(new_node, NODE_ACTIVE);
  list_append(proc_list, new_node);
  free_ary(cmd_args, MAX_INPUT_LENGTH);
  return 0;
}

int run_cmd(char **cmd_ary, Node *proc_list) {
  if(!cmd_ary[0]) { return -1; } // no command given

  // run handler if command matches
  if(strcmp(cmd_ary[0], "bg") == 0) {
    bg(cmd_ary, proc_list);
  }
  else if(strcmp(cmd_ary[0], "bgkill") == 0) { // run handler if command is bgkill
    bgkill(cmd_ary, proc_list);
  }
  else if(strcmp(cmd_ary[0], "bglist") == 0) { // run handler if command is bglist
    bglist(proc_list);
  }
  else if(strcmp(cmd_ary[0], "bgstop") == 0) { // run handler if command is bgstop
    bgstop(cmd_ary, proc_list);
  }
  else if(strcmp(cmd_ary[0], "bgstart") == 0) { // run handler if command is bgstart
    bgstart(cmd_ary, proc_list);
  }
  else {
    printf("%s: command not found\n", cmd_ary[0]);
  }
  return 0;
}

int bgstart(char **cmd_ary, Node *proc_list) {
  if(!cmd_ary[1]) {
    printf("No pid given\n. bgstart requires a pid.\n");
    return -1;
  }

  int pid = atoi(cmd_ary[1]);

  Node *child = find_node(proc_list, pid);
  if(child) {
    if(child->status == NODE_ACTIVE) {
      printf("Process with pid %i is already running\n", pid);
      return -1;
    }
    printf("starting pid %i\n", pid);
    kill(pid, SIGCONT);
    set_node_status(proc_list, NODE_INACTIVE);
  }
  else {
    printf("No child process with pid %i.\n", pid);
  }

  return 0;
}

int bgstop(char **cmd_ary, Node *proc_list) {
  if(!cmd_ary[1]) {
    printf("No pid given\n. bgstop requires a pid.\n");
    return -1;
  }

  int pid = atoi(cmd_ary[1]);
  Node *child = find_node(proc_list, pid);
  if(child) {
    if(child->status == NODE_INACTIVE) {
      printf("Process with pid %i is already stopped\n", pid);
      return -1;
    }
    printf("stopping pid %i\n", pid);
    kill(pid, SIGSTOP);
    set_node_status(child, NODE_INACTIVE);
  }
  else {
    printf("No child process with pid %i.\n", pid);
  }

  return 0;
}

void bglist(Node *proc_list) {
  int num_bg = 0;

  Node *curr = proc_list->next;
  while(curr) {
    num_bg++;
    printf("%i: ", curr->val);
    if(curr->name) {
      printf("%s\n", curr->name);
    }
    curr = curr->next;
  }
  printf("Total background jobs: %i\n", num_bg);
}

void bgkill(char **cmd_ary, Node *proc_list) {
  if(!cmd_ary[1]) {
    printf("No pid given\n. bgkill requires a pid.\n");
    return;
  }

  int pid = atoi(cmd_ary[1]);

  if(find_node(proc_list, pid)) {
    printf("killing pid %i\n", pid);
    kill(pid, 15);
    delete_node(proc_list, pid);
  }
  else {
    printf("No child process with pid %i.\n", pid);
  }
  // handle undying process?
}

int reap_zombie_children(Node *proc_list) {
  Node *curr = proc_list->next; // first actual node
  while(curr) {
    int status;
    if(waitpid(curr->val, &status, WNOHANG) > 0) { // process exited
      printf("child process with pid %i exited. removing from list.\n", curr->val);
      delete_node(proc_list, curr->val);
    }
    curr = curr->next;
  }
}

int main(int argc, char **argv) {
  Node *proc_list = create_node(-1); // process list has a dummy head node with val -1
  while(1) {
    char *input;
    input = prompt_and_accept_input();
    char **cmd_ary = parse_input(input);

    reap_zombie_children(proc_list);
    run_cmd(cmd_ary, proc_list);

    free_ary(cmd_ary, MAX_INPUT_LENGTH);
    free(input);
  }
}

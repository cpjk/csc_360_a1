#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

// append a Node to the end of the list starting with head
void list_append(Node *head, Node *new_node) {
  Node *curr = head;
  while(curr->next) { // traverse to end of list
    curr = curr->next;
  }
  curr->next = new_node; // append Node to tail of list
}

void set_node_val(Node *node, int val) {
  node -> val = val;
}

Node *create_node(int val) {
  Node *new_node = malloc(sizeof(Node));
  new_node->val = val;
  new_node->next = NULL;
  return new_node;
}

void print_node(Node *node) {
  printf("%i\n", node->val);
}

void print_list(Node *head) {
  Node *curr = head;
  while(1) {
    printf("%i\n", curr->val);
    if(!curr->next) return;
    curr = curr->next;
  }
}


int main(int argc, char **argv) {
  Node *linked_list = create_node(1);
  list_append(linked_list, create_node(2));
  list_append(linked_list, create_node(3));
  list_append(linked_list, create_node(4));
  list_append(linked_list, create_node(5));
  list_append(linked_list, create_node(6));
  print_list(linked_list);
}

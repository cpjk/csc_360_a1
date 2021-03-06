#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// append a Node to the end of the list starting with head
void list_append(Node *head, Node *new_node) {
  Node *curr = head;
  while(curr->next) { // traverse to end of list
    curr = curr->next;
  }
  curr->next = new_node; // append Node to tail of list
}

void set_node_name(Node *node, char *name) {
  int len = (strlen(name)+1);
  char *node_name = malloc(sizeof(char)*len);
  int i = 0;
  for(i; i < len; i++) { // flush string
    node_name[i] = '\0';
  }
  strcpy(node_name, name);
  node->name = node_name;
}

void set_node_val(Node *node, int val) {
  node -> val = val;
}

void set_node_status(Node *node, int status) {
  node -> status = status;
}

// delete the node containing val from the list, if it is present.
// returns the new head of the list. returns NULL if
// the new list is empty.
// make sure to use the return value as the new list
Node *delete_node(Node *head, int val) {
  if(head->val == val) { // if head is the val
    Node *new_head = head->next;
    free(head->name);
    free(head);
    return new_head;
  }

  Node *prev = head;
  Node *curr = head->next;
  while(curr) { // if the val is not the head
    if(curr->val == val) {
      prev->next = curr->next;
      free(curr->name);
      free(curr);
      return head;
    }
    prev = curr;
    curr = curr->next;
  }
  return head;
}

// Searches for a node with the given val in the linked list
// pointed to by head.
// Returns the target node if found. Otherwise, returns NULL
Node *find_node(Node *head, int val) {
  if(head->val == val) { // if head is the val
    return head;
  }

  Node *prev = head;
  Node *curr = head->next;
  while(curr) { // if the val is not the head
    if(curr->val == val) {
      return curr;
    }
    prev = curr;
    curr = curr->next;
  }
  return NULL;
}

// Creates a new node and returns a pointer to it
Node *create_node(int val) {
  Node *new_node = malloc(sizeof(Node));
  new_node->val = val;
  new_node->name = NULL;
  new_node->next = NULL;
  new_node->status = NODE_INACTIVE;
  return new_node;
}

void print_node(Node *node) {
  printf("%i\n", node->val);
}

// prints a list
void print_list(Node *head) {
  int num_bg = 0;

  if(!head) return;
  Node *curr = head;
  while(1) {
    if(curr->status) {
      num_bg++;
      printf("%i: ", curr->val);
      if(curr->name) {
        printf("%s\n", curr->name);
      }
    }
    if(!curr->next) {
      printf("Total background jobs: %i\n", num_bg);
      return;
    }
    curr = curr->next;
  }
}

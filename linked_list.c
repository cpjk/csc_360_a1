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

// delete the node containing val from the list, if it is present.
// returns the new head of the list. returns NULL if
// the new list is empty.
Node *delete_node(Node *head, int val) {
  if(head->val == val) { // if head is the val
    Node *new_head = head->next;
    free(head);
    return new_head;
  }

  Node *prev = head;
  Node *curr = head->next;
  while(curr) { // if the val is not the head
    if(curr->val == val) {
      prev->next = curr->next;
      free(curr);
      return head;
    }
    prev = curr;
    curr = curr->next;
  }
  return head;
}

int find_node(Node *head, int val) {
  if(head->val == val) { // if head is the val
    return 1;
  }

  Node *prev = head;
  Node *curr = head->next;
  while(curr) { // if the val is not the head
    if(curr->val == val) {
      return 1;
    }
    prev = curr;
    curr = curr->next;
  }
  return 0;
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
  if(!head) return;
  Node *curr = head;
  while(1) {
    printf("%i\n", curr->val);
    if(!curr->next) return;
    curr = curr->next;
  }
}


/* int main(int argc, char **argv) { */
/*   Node *linked_list = create_node(1); */
/*   list_append(linked_list, create_node(2)); */
/*   list_append(linked_list, create_node(3)); */
/*   list_append(linked_list, create_node(4)); */
/*   list_append(linked_list, create_node(5)); */
/*   list_append(linked_list, create_node(6)); */
/*   find_node(linked_list, 1); */
/*   find_node(linked_list, 2); */
/*   find_node(linked_list, 6); */
/*   find_node(linked_list, 0); */
  /* print_list(linked_list); */
  /* printf("\n"); */
  /* linked_list = delete_node(linked_list, 1); */
  /* print_list(linked_list); */
  /* linked_list = delete_node(linked_list, 3); */
  /* print_list(linked_list); */
  /* linked_list = delete_node(linked_list, 6); */
  /* linked_list = delete_node(linked_list, 2); */
  /* linked_list = delete_node(linked_list, 4); */
  /* linked_list = delete_node(linked_list, 4); */
  /* printf("\n"); */
  /* print_list(linked_list); */
  /* linked_list = delete_node(linked_list, 5); */
  /* printf("\n"); */
  /* print_list(linked_list); */
/* } */

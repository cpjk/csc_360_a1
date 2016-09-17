typedef struct Node {
  int val;
  struct Node *next;
} Node;

Node *create_node();
void list_append();
void set_node_val();
Node *delete_node();

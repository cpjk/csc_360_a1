typedef struct Node {
  int val;
  struct Node *next;
} Node;

Node *create_node(int);
void list_append();
void set_node_val();
Node *delete_node();
void print_list(Node *);
int find_node(Node *, int);

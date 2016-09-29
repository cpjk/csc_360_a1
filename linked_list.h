typedef struct Node {
  int val;
  int status;
  char *name;
  struct Node *next;
} Node;

Node *create_node(int);
void list_append();
void set_node_val();
void set_node_name();
void set_node_status();
Node *delete_node();
void print_list(Node *);
int find_node(Node *, int);

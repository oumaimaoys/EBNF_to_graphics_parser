
typedef struct node_S *tree; // pointer to first node which defines the tree
typedef struct node_S {
    char* info;
    tree left; 
    tree right;
} node;

tree initiate_tree();

tree create_node(char* data);

void read_tree(tree root);
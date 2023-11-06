
typedef struct node_S *tree; // pointer to first node which defines the tree
typedef struct node_S {
    char* info;
    tree successor; // successors in a list, and the node point to the first element;
    tree next_sibling;
} node;

tree initiate_tree();

tree create_node(char* data);

void read_tree(tree root, int new_line);
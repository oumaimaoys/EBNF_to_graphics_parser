
typedef struct node_S *tree; // pointer to first node which defines the tree
typedef struct node_S {
    char info[30];
    tree successor; // successors in a list, and the node point to the first element;
    tree next_sibling;
} node;

tree initiate_tree();

tree create_node(char info[30]);

void add_sibling(tree node, tree previous_sibling);

void add_successor(tree node, tree predecessor);

void browse_tree(tree t);
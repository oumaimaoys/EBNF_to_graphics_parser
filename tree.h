#ifndef TREE_H
#define TREE_H

typedef enum{
    ID,
    LITERAL,
    RECURSSIVE,
    OPTIONAL,
    ALTERNATIVE,
    PARENT,
    NULL_TYPE,
} NodeType;

typedef struct node_L {
    void* child;
    struct node_L* nextNode;
} list;


typedef struct node_S *tree; // pointer to first node which defines the tree
typedef struct node_S {
    NodeType type;
    char *info; // not null only if type == id or literal
    list* children;
} node;


tree initiate_tree();

tree create_node(char *data, NodeType type);

list* init_list();

void push(list* my_list, tree item);

list* concactenate(list* list_1, list* list_2);

void displayTree(tree root);

int count_leaves(tree root);

#endif /* TREE_H */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

tree initiate_tree(){
    tree new = malloc(sizeof(node));
    strcpy(new->info, ""); 
    new->successor = NULL;
    new->next_sibling = NULL;
    return new;
}


tree create_node(char data[30]){
    tree new = malloc(sizeof(node));
    strcpy(new->info, data);
    new->successor = NULL;
    new->next_sibling = NULL;
    return new;
}

void add_sibling(tree node, tree previous_sibling){
    previous_sibling->next_sibling = node;
}

void add_successor(tree node, tree predecessor){
    predecessor->successor = node;
}

void browse_tree(tree t){

}
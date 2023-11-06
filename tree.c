#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C:/Users/lenovo/Documents/insea2023/compilateur/tree.h"

tree initiate_tree(){
    tree new = malloc(sizeof(node));
    strcpy(new->info, ""); 
    new->successor = NULL;
    new->next_sibling = NULL;
    return new;
}


tree create_node(char* data) {
    tree new = malloc(sizeof(node));
    if (new != NULL) {
        size_t info_len = strlen(data);
        new->info = malloc(info_len + 1); 
        if (new->info != NULL) {
            strcpy(new->info, data);
            new->info[info_len] = '\0';
        } else {
            free(new);
            return NULL;
        }
        new->successor = NULL;
        new->next_sibling = NULL;
    }
    return new;
}


void read_tree(tree root, int new_line) {
    if (root == NULL) {
        return; 
    }

    printf("%s", root->info);

    if (root->successor != NULL) {
        printf("\n");
    }

    // Recursively traverse the successor (children) of the current node with a new_line flag
    read_tree(root->successor, 1);

    if (root->next_sibling != NULL) {
        // If there are next siblings, print them on the same line
        printf(" ");
    } else if (new_line) {
        // If no next sibling and there are successors, print an extra newline
        printf("\n");
    }

    // Recursively traverse the next sibling of the current node without a new_line flag
    read_tree(root->next_sibling, 0);
}
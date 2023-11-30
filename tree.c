#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C:/Users/lenovo/Documents/insea2023/compilateur/tree.h"

tree initiate_tree(){
    tree new = malloc(sizeof(node));
    strcpy(new->info, ""); 
    new->left = NULL;
    new->right = NULL;
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
        new->left = NULL;
        new->right = NULL;
    }
    return new;
}

void read_tree(tree root) {
    if (root != NULL) {
        // Print the current node's data
        printf("%d ", root->info);

        // Recursively print the left and right subtrees
        read_tree(root->left);
        read_tree(root->right);
    }
}
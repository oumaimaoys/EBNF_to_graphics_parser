#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C:/Users/lenovo/Documents/insea2023/compilateur/tree.h"


tree initiate_tree(){
    tree new = malloc(sizeof(node));
    new->type = NULL_TYPE;
    new->info = NULL; 
    new->children = NULL;
    return new;
}

list* init_list() {
    list* newNode = (list*)malloc(sizeof(list));
    newNode->child = NULL;
    newNode->nextNode = NULL;

    return newNode;
}

void push(list* myList, tree item) {
    list *newNode = (list *)malloc(sizeof(list));
    if (newNode == NULL) {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }

    newNode->child = (void*)item;
    newNode->nextNode = NULL;

    // Set the tree node and update the pointers
    if(myList->child != NULL){
        list *p = myList;
        while (p->nextNode != NULL) {
            p = p->nextNode;
        }
        p->nextNode = newNode;
    } else {
        myList->child = (void*)item;
    }

}

tree create_node(char* data, NodeType type) {
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
        new->type = type;
        new->children = NULL;
    }
    return new;
}

list* concactenate(list* list_1, list* list_2){
    if(list_1 != NULL){
        list* p = list_1;
        while( p->nextNode != NULL){
            p = p->nextNode;
        }
        p->nextNode = list_2;
    }
    else{

        return list_2;
    }

    return list_1;
    
}

void displayTreeHelper(tree root, int level) {
    if (root == NULL) {
        return;
    }

    // Print current node
    for (int i = 0; i < level; i++) {
        printf("\n"); // Two spaces for each level
    }
    for (int i = 0; i < level; i++) {
        printf("  "); // Two spaces for each level
    }

    const char* typeString;
    switch (root->type) {
        case ID:
            typeString = "IDENTIFIER";
            break;
        case LITERAL:
            typeString = "LITERAL";
            break;
        case RECURSSIVE:
            typeString = "REC";
            break;
        case OPTIONAL:
            typeString = "OPT";
            break;
        case ALTERNATIVE:
            typeString = "ALT";
            break;
        case NULL_TYPE:
            typeString = "NULL";
            break;
        case PARENT:
            typeString = "PAR";
            break;
        default:
            typeString = "UNKNOWN";
            break;
    }
    printf("(%s[%s],%d )", typeString, root->info,level);

    // Recursively display children
    list *currentChild = root->children;
    while (currentChild != NULL) {
        displayTreeHelper((tree)(currentChild->child), level + 1);
        currentChild = currentChild->nextNode;
    }

    
}

void displayTree(tree root) {
    displayTreeHelper(root, 0);
}

int count_leaves(tree root){
    if (root == NULL) {
        return 0;
    }

    // If the node is a leaf and not of ALTERNATIVE type, return 1
    if (root->type != ALTERNATIVE && root->children == NULL) {
        return 1;
    }

    // Initialize count to 0
    int count = 0;

    // Traverse the children and sum up the counts
    list* currentChild = root->children;
    if (root->type != ALTERNATIVE){
        while (currentChild != NULL) {
            tree childNode = (tree)(currentChild->child);
            count += count_leaves(childNode);
            currentChild = currentChild->nextNode;
        }
    }
    else{
        count = 1;
    }
   

    return count;
}
#include <stdio.h>
#include "tree.h"

// we gonna assume for now that the input's syntax is correct 

tree parse_program(char* source_code){
    tree parse_tree = initiate_tree(); // we create an emptry tree node
    char* root = parse_identifier(source_code)->info; // we parse the root 
    strcpy(parse_tree->info, root); // we put the identifier in the root, which is the starting token
    
    // we get the slice after = to get the expression because ebnf : token = experession
    int startIndex = 0;
    for(int i = 0; source_code[i] != "=" ; i++){
        startIndex++;
    }

    int sliceLength = strlen(source_code) - startIndex;
    char* slice = (char*)malloc(sliceLength + 1);
    strncpy(slice, source_code + 0, sliceLength);
    slice[sliceLength] = '\0';

    // we parse the expression
    parse_expression(slice);

    return parse_tree;

}

void parse_expression(char* source_code){
    // there are three types of expressions

    // expression starts with (

    // expression stars with letter/number

    // expression starts with {

    // expression starts with [
}

void parse_alternatives(char* source_code){}

void parse_optionals(char* source_code){}

void parse_recurssives(char* source_code){}

tree parse_identifier(char* source_code){

}
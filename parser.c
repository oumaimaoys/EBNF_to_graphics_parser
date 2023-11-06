#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "C:/Users/lenovo/Documents/insea2023/compilateur/parser.h" 

// helper functions
char* slice_string(const char* source, int startIndex) {
    return strdup(source + startIndex);
}

char* slice_prefix(const char* source, int endIndex){
    size_t sliceLength = endIndex;
    char* slicedString = (char*)malloc(sliceLength + 1);
    if (slicedString != NULL) {
        strncpy(slicedString, source, sliceLength);
        slicedString[sliceLength] = '\0';
    }
    return slicedString;
}

int isValid(const char* code){
    int flag = 1;
    if((strlen(code)==0) || (strlen(code)==1 && !isalpha(code[0]))){
        flag = 0;
    }
    return flag;
}
int isTerminal(const char* text) { // returns 1 if terminal
    int len = strlen(text);
    if (len == 0) {
        return 0;  
    }
    // Check if the text is enclosed in double quotes
    if (text[0] == '"' && text[len - 1] == '"' && len > 1) {
        // Check if there are only alphanumeric characters between quotes
        for (int i = 1; i < len - 1; i++) {
            if (!isalnum(text[i])) {
                return 0;  
            }
        }
        return 1; 
    }
    for (int i = 0; i < len; i++) {
        if (!isalnum(text[i]) || isspace(text[i])) {
            return 0;  
        }
    }
    return 1; 
}

// we gonna assume for now that the input's syntax is correct 

tree parse_program(char* source_code){
    char* root = parse_identifier(source_code)->info; // we parse the root 
    tree parse_tree = create_node(root);
    
    // we get the slice after = to get the expression because ebnf : token = experession
    int startIndex = 0;
    for(int i = 0; source_code[i] != '=' ; i++){
        startIndex++;
    }
    char* slice = slice_string(source_code, startIndex + 1);
    
    // we parse the expression
    parse_tree->successor = parse_expression(slice);

    return parse_tree;
}

tree parse_expression(char* source_code){
    if (source_code == NULL || *source_code == '\0') {
        return NULL;  
    }

    int terminal = 1;

    tree expression_node = NULL;

    switch (*source_code) {
        case '(':
            expression_node = parse_parentheses(source_code + 1);
            break;
        case '{':
            expression_node = parse_recurssives(source_code + 1);
            break;
        case '[':
            expression_node = parse_optionals(source_code + 1);
            break;
        case '"':
            expression_node = parse_literal(source_code);
            break;
        case '|':
            expression_node = parse_expression(source_code + 1);
            break;
        default:
            if (isalpha(*source_code)) {
                expression_node = parse_identifier(source_code);
                terminal = 0;
            }
            else{
                expression_node = parse_expression(source_code + 1);
            }
    }
    if (expression_node != NULL) {
        char* remaining_code = source_code + strlen(expression_node->info);
        printf("%s", expression_node->info);
        // checks if the node is not terminal
        if(isTerminal(expression_node->info) == 0 ){
            printf("not terminal");
            expression_node->successor = parse_expression(expression_node->info);
        }
        // only in the case where there is a remaining
        if(isValid(remaining_code) == 1){
            printf("valid");
            expression_node->next_sibling = create_node(remaining_code);
            expression_node->next_sibling->successor = parse_expression(remaining_code);
        }
    }
    
    return expression_node;
}

tree parse_parentheses(char* source_code){
    int par_flag = 0; // initially false, turns true for open parentheses adn false when parentheses closes
    int char_len = strlen(source_code);
    int endIndex = char_len;

    for(int i = 0; source_code[i]< char_len ;i++){
        if(source_code[i] == '('){
            par_flag = 1;
        }
        else if(par_flag == 1 && source_code[i] == ')'){
            par_flag = 0;
        }
        else if(par_flag == 0 && source_code[i] == ')'){
            endIndex = i - 1;
            break;
        }
    }
    char* inside_par_slice = slice_prefix(source_code, endIndex);
    tree new_node = create_node(inside_par_slice); // (inside)
    
    return new_node;
    
}

tree parse_optionals(char* source_code){
    int brackets_flag = 0; // initially false, turns true for open parentheses adn false when parentheses closes
    int char_len = strlen(source_code);
    int endIndex = char_len;

    for(int i = 0; source_code[i]< char_len ;i++){
        if(source_code[i] == '['){
            brackets_flag = 1;
        }
        else if(brackets_flag == 1 && source_code[i] == ']'){
            brackets_flag = 0;
        }
        else if(brackets_flag == 0 && source_code[i] == ']'){
            endIndex = i - 1;
            break;
        }
    }
    // A = [U] : A = U, A = 0
    char* slice = slice_prefix(source_code, endIndex);
    tree new_node = create_node(slice); // U
    tree empty_node = create_node("0"); // 0 , also points back to new_node to indicate the recurssivite
    new_node->next_sibling = empty_node;
    
    return new_node;
}

tree parse_recurssives(char* source_code){
    int flag = 0; // initially false, turns true for open parentheses adn false when parentheses closes
    int char_len = strlen(source_code);
    int endIndex = char_len;

    for(int i = 0; source_code[i]< char_len ;i++){
        if(source_code[i] == '{'){
            flag = 1;
        }
        else if(flag == 1 && source_code[i] == '}'){
            flag = 0;
        }
        else if(flag == 0 && source_code[i] == '}'){
            endIndex = i - 1;
            break;
        }
    }
    // A = {U} : A = UA, A = 0
    char* recurssive_slice = slice_prefix(source_code, endIndex);
    tree new_node = create_node(recurssive_slice); // UA
    tree empty_node = create_node("0"); // 0 , also points back to new_node to indicate the recurssivite
    empty_node->next_sibling = new_node; // ?
    new_node->next_sibling = empty_node;
    
    return new_node;
}

tree parse_literal(char* source_code){ // anything betwenn ""
    int char_len = strlen(source_code);
    int endIndex = char_len;

    for(int i = 0; source_code[i]< char_len ;i++){
        if(source_code[i] == '"'){
           endIndex = i;
           break;
        }
    }

    char* literal_slice = slice_prefix(source_code, endIndex);
    tree new_node = create_node(literal_slice); // (inside)
    
    return new_node;
}

tree parse_identifier(char* source_code){
    int char_len = strlen(source_code);
    int endIndex = 0;

    while (endIndex < char_len && (isalpha(source_code[endIndex]) || isdigit(source_code[endIndex]))) {
        endIndex++;
    }

    int identifier_len = endIndex;
    if (identifier_len > 0) {
            char* identifier = slice_prefix(source_code, identifier_len);
            tree new = create_node(identifier);
            return new;
        }

    return NULL;
   
}
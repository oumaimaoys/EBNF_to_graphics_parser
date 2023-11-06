#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "parser.h" 

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

// we gonna assume for now that the input's syntax is correct 

tree parse_program(char* source_code){
    char* root = parse_expression(source_code)->info; // we parse the root 
    tree parse_tree = create_node(root);
    
    // we get the slice after = to get the expression because ebnf : token = experession
    int startIndex = 0;
    for(int i = 0; source_code[i] != "=" ; i++){
        startIndex++;
    }
    char* slice = slice_string(source_code, startIndex);

    // we parse the expression
    parse_tree->successor = parse_expression(slice);

    return parse_tree;
}

tree parse_expression(char* source_code){
    // there are three types of expressions
    int len = strlen(source_code);
    int index = -1; // ending index to create node to
    

    switch (*source_code) {
        case '(':
            index = parse_parentheses(source_code + 1);
            break;
        case '{':
            index = parse_recurssives(source_code + 1);
            break;
        case '[':
            index = parse_optionals(source_code + 1);
            break;
        case '"':
            index = parse_literal(source_code + 1);
            break;
        case '|':
            index = parse_alternatives(source_code + 1);
            break;
        case ' ':
            break;
        default:
            if (isalpha(*source_code)) {
                index = parse_identifier(source_code);
            }
    }

    if(index!=-1){
        char* data_1 = slice_prefix(source_code, index);
        char* date_2 = slice_string(source_code, index + 1);
        tree expression_node = create_node(data_1);
        tree expression_node_2 = create_node(date_2);
        expression_node->next_sibling = expression_node_2;
        
        tree expression_node_parsed = parse_expression(expression_node->info);
        tree expression_node_2_parsed = parse_expression(expression_node_2->info);
        expression_node->successor = expression_node_parsed;
        expression_node_2->successor = expression_node_2_parsed;
        return expression_node;
    }
    else{
        source_code = source_code + 1; //?
        return NULL;
    }
    
}

int parse_parentheses(char* source_code){
    int par_flag = 0; // initially false, turns true for open parentheses adn false when parentheses closes
    int char_len = strlen(source_code);
    int endIndex = strlen;

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
    return endIndex;
}

int parse_alternatives(char* source_code){

}

int parse_optionals(char* source_code){
    int brackets_flag = 0; // initially false, turns true for open parentheses adn false when parentheses closes
    int char_len = strlen(source_code);
    int endIndex = strlen;

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
    return endIndex;
}

int parse_recurssives(char* source_code){
    int flag = 0; // initially false, turns true for open parentheses adn false when parentheses closes
    int char_len = strlen(source_code);
    int endIndex = strlen;

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
    return endIndex;
}

int parse_literal(char* source_code){ // anything betwenn ""
    int char_len = strlen(source_code);
    int endIndex = strlen;

    for(int i = 0; source_code[i]< char_len ;i++){
        if(source_code[i] == '"'){
           endIndex = i-1;
           break;
        }
    }
    
    return endIndex;
}

int parse_identifier(char* source_code){
    int char_len = strlen(source_code);
    int endIndex = 0;

    while (endIndex < char_len && (isalpha(source_code[endIndex]) || isdigit(source_code[endIndex]))) {
        endIndex++;
    }

    return endIndex - 1;
   
}
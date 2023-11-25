#include "lexer.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

char* extract_substring(char* p1, int length) {
    char* var = (char*)malloc(length + 1);
    if (var == NULL) {
        exit(EXIT_FAILURE);
    }
    strncpy(var, p1, length);
    var[length] = '\0';
    return var;
}

Token* new_token(char* type, char* value) {
    Token* newToken = (Token*)malloc(sizeof(Token));

    if (newToken == NULL) {
        exit(EXIT_FAILURE);
    }    
    newToken->type = strdup(type);
    newToken->value = strdup(value);
    newToken->next = NULL;

    return newToken;
}

Token* scan_token(char* input){
    Token* token; 
    char* p1 = input;
    switch (*p1){
        case '(':
            token = new_token("LPar", "(");
            break;
        case ')':
            token = new_token("RPar", ")");
            break;
        case '[':
            token = new_token("LBrak", "[");
            break;
        case ']':
            token = new_token("RBrak", "]");
            break;
        case '{':
            token = new_token("LBrace", "{");
            break;
        case '}':
            token = new_token("Rbrace", "}");
            break;
        case '|':
            token = new_token("Bar", "|");
            break;
        case '=':
            token = new_token("Eql", "=");
            break;
        case '\"':
            p1++;
            while(*p1 != '\"'){
                p1++;
            }
            size_t length = p1 - input + 1;
            char* value = extract_substring(input, length);
            token = new_token("Literal", value);
            break;
        default:
            if(isalnum(*p1)){
                while(isalnum(*p1)){
                    p1++;
                }
                size_t length = p1 - input;
                char* value = extract_substring(input, length);
                token = new_token("Identifier", value);
            }
            break;
    }

    return token;
}

Token* lexer(char* expression){
    char* p1 = expression;
    int exp_len = strlen(expression);
    Token* token_list = NULL;
    Token* previous = NULL;

    while (*p1 != '\0'){
        if(*p1 != ' '){
            Token* temp = scan_token(p1);   
            if (token_list == NULL) {
                token_list = temp;  
            }
            if (previous != NULL) {
                previous->next = temp;  
            }
            int len_temp = strlen(temp->value);
            p1 = p1 + len_temp;
            previous = temp;
        }
        else{
            p1++;
        }

    }

    return token_list;
}

void displayTokenList(Token* head) {
    printf("Token List:\n");

    while (head != NULL) {
        printf("%s[Value: %s] ", head->type, head->value);
        head = head->next;
    }
}

int main(){
    char input_ebnf[100];

    fgets(input_ebnf, sizeof(input_ebnf), stdin);

    // Remove the newline character at the end, if present
    size_t len = strlen(input_ebnf);
    if (len > 0 && input_ebnf[len - 1] == '\n') {
        input_ebnf[len - 1] = '\0';
    }

    Token* parse_tree = lexer(input_ebnf);
    displayTokenList(parse_tree);

    return 0;
}
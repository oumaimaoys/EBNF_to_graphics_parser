#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "C:/Users/lenovo/Documents/insea2023/compilateur/lexer.h"


char* extract_substring(char* p1, int length) {
    char* var = (char*)malloc(length + 1);
    if (var == NULL) {
        exit(EXIT_FAILURE);
    }
    strncpy(var, p1, length);
    var[length] = '\0';
    return var;
}

Token* new_token(TokenType type, char* value) {
    Token* newToken = (Token*)malloc(sizeof(Token));

    if (newToken == NULL) {
        exit(EXIT_FAILURE);
    }    
    newToken->type = type;
    newToken->value = strdup(value);
    newToken->next = NULL;

    return newToken;
}

Token* scanToken(char* input){
    Token* token; 
    char* p1 = input;
    switch (*p1){
        case '(':
            token = new_token(LPar, "(");
            break;
        case ')':
            token = new_token(RPar, ")");
            break;
        case '[':
            token = new_token(LBrak, "[");
            break;
        case ']':
            token = new_token(RBrak, "]");
            break;
        case '{':
            token = new_token(LBrace, "{");
            break;
        case '}':
            token = new_token(RBrace, "}");
            break;
        case '|':
            token = new_token(Bar, "|");
            break;
        case '=':
            token = new_token(Eql, "=");
            break;
        case ';':
            token = new_token(SemiColon, ";");
            break;
        case '\"':
            p1++;
            while(*p1 != '\"'){
                p1++;
            }
            size_t length = p1 - input + 1;
            char* value = extract_substring(input, length);
            token = new_token(Literal, value);
            break;
        default:
            if(isalnum(*p1)){
                while(isalnum(*p1)){
                    p1++;
                }
                size_t length = p1 - input;
                char* value = extract_substring(input, length);
                token = new_token(Identifier, value);
            }
            else{
                printf("\nError: invalid symbol!");
                exit(EXIT_FAILURE);
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
            Token* temp = scanToken(p1);   
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
        // Map TokenType to corresponding strings for display
        const char* typeString;
        switch (head->type) {
            case Identifier:
                typeString = "IDENTIFIER";
                break;
            case Literal:
                typeString = "LITERAL";
                break;
            case LPar:
                typeString = "LPar";
                break;
            case RPar:
                typeString = "RPar";
                break;
            case LBrak:
                typeString = "LBrak";
                break;
            case RBrak:
                typeString = "RBrak";
                break;
            case LBrace:
                typeString = "LBrace";
                break;
            case RBrace:
                typeString = "RBrace";
                break;
            case Bar:
                typeString = "Bar";
                break;
            case Eql:
                typeString = "Eql";
                break;
            case SemiColon:
                typeString = "SEmicolon";
                break;
            default:
                typeString = "UNKNOWN";
                break;
        }

        printf("%s[Value: %s] ", typeString, head->value);
        head = head->next;
    }

    printf("\n");
}
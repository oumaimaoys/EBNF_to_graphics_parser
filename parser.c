#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "C:/Users/lenovo/Documents/insea2023/compilateur/lexer.h"
#include "C:/Users/lenovo/Documents/insea2023/compilateur/parser.h" 

int parser(Token* input){
    parse_production(input);
    return 1;
}

void parse_production(Token* input){ // program: ident = expression
    Token* p = input;
    if(strcmp(p->type, "Identifier") == 0){
        p= p->next;
        if (strcmp(p->type, "Eql") == 0){
            p= p->next;
        }
        else{
            printf("expected '='");
            exit(EXIT_FAILURE);
        }
    }
    else{
        printf("expected 'identifier'");
        exit(EXIT_FAILURE);
    }
    parse_expression(p);
}

void parse_expression(Token* input){
    Token* p = input;
    parse_term(p);
    p= p->next;
    while(strcmp(p->type, "Bar") == 0){
        p = p->next;
        parse_term(p);
    }
}

void parse_term(Token* input){
    Token* p = input;
    while((strcmp(p->type, "Identifier") == 0 ) || (strcmp(p->type, "Literal") == 0) || (strcmp(p->type, "LPar") == 0) || (strcmp(p->type, "LBrak") == 0) || (strcmp(p->type, "LBrace") == 0)){
        parse_factor(p);
        p = p->next;
    }
}

void parse_factor(Token* input){
    Token* p = input;
    if (strcmp(p->type, "Identifier") == 0){
        p = p->next;
    }
    else if (strcmp(p->type, "Literal") == 0 ){
        p = p->next;
    }
    else if (strcmp(p->type, "LPar") == 0){
        p = p->next;
        parse_expression(p);
        if(strcmp(p->type, "RPar") == 0){
            p = p->next;
        }
        else{
            printf("expected ')' ");
            exit(EXIT_FAILURE);
        }
    }
    else if(strcmp(p->type, "LBrak") == 0){
        p = p->next;
        parse_expression(p);
        if(strcmp(p->type, "RBrak") == 0){
            p = p->next;
        }
        else{
            printf("expected ']' ");
            exit(EXIT_FAILURE);
        }
    }
    else if (strcmp(p->type,"LBrace") == 0){
        p=p->next;
        parse_expression(p);
        if(strcmp(p->type,"RBrace") == 0){
            p = p->next;
        }
        else{
            printf("expected '}' ");
            exit(EXIT_FAILURE);
        }
    }
    else{
        printf("error : syntax");
        exit(EXIT_FAILURE);
    }
}
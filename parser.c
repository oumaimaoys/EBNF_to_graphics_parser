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

void parse_production(Token* p){ // program: ident = expression
    printf(" 1 called");
    if(strcmp(p->type, "Identifier") == 0){
        p= p->next;
        if (strcmp(p->type, "Eql") == 0){
            p= p->next;
            parse_expression(p);
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
    
    
}

void parse_expression(Token* p){
    printf(" 2 called");
    if (p != NULL){
        parse_term(p);
        p= p->next;
        while(strcmp(p->type, "Bar") == 0){
            p = p->next;
            parse_term(p);
        }
    }
    else{
        printf("expected expression");
        exit(EXIT_FAILURE);
    }

}

void parse_term(Token* p){
    printf(" 3 called");
    while((strcmp(p->type, "Identifier") == 0 ) || (strcmp(p->type, "Literal") == 0) || (strcmp(p->type, "LPar") == 0) || (strcmp(p->type, "LBrak") == 0) || (strcmp(p->type, "LBrace") == 0)){
        parse_factor(p);
        p = p->next;
    }
    
}

void parse_factor(Token* p){
    printf(" 4 called");
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
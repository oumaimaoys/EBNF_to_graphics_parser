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
    if( p->type == Identifier ){
        p= p->next;
        if ( p->type == Eql ){
            p= p->next;
            p = parse_expression(p);
        }
        else{
            printf("\nerror: expected '='");
            exit(EXIT_FAILURE);
        }
    }
    else{
        printf("\nerror: expected 'Identifier'");
        exit(EXIT_FAILURE);
    }
    
}

Token* parse_expression(Token* p){
    printf(" 2 called");
    if (p != NULL){
        p = parse_term(p);
        while( p->type == Bar ){
            p = p->next;
            p = parse_term(p);
        }
    }
    else{
        printf("\nerror: expected expression");
        exit(EXIT_FAILURE);
    }
    return p;
}

Token* parse_term(Token* p){
    printf(" 3 called");
    while(( p->type == Identifier ) || ( p->type == Literal) || ( p->type == LPar ) || ( p->type == LBrak) || ( p->type == LBrace)){
        p = parse_factor(p);
    }
    return p;
}

Token* parse_factor(Token* p){
    printf(" 4 called");
    switch (p->type){
        case Identifier:
            printf("here");
            p = p->next;
            break;
        case Literal:
            p = p->next;
            break;
        case LPar:
            p = p->next;
            p = parse_expression(p);
            if( p->type == RPar ){
                p = p->next;
            }
            else{
                printf("\nerror : expected ')' ");
                exit(EXIT_FAILURE);
            }
            break;
        case LBrak:
            p = p->next;
            p = parse_expression(p);
            if( p->type == RBrak ){
                p = p->next;
            }
            else{
                printf("\nerror : expected ']' ");
                exit(EXIT_FAILURE);
            }
            break;
        case LBrace:
            p = p->next;
            p = parse_expression(p);
            if( p->type == RBrace ){
                p = p->next;
            }
            else{
                printf("\nerror : expected '}' ");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            printf("\nerror : syntax");
            exit(EXIT_FAILURE);
            break;
    }
    return p;
}
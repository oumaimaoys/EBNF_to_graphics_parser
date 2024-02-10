#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../my_headers/lexer.h"
#include "../my_headers/parser.h" 
 

Token* next_token;

void scan_token(){ // advances next_token
    next_token = next_token->next;
}

tree parser(Token* input){
    next_token = input;
    tree parse_tree = parse_production();
    if(parse_tree != NULL){
        return parse_tree;
    }
    else{
        printf("\nerror: parsing failed\n");
        return NULL;
    }
}

tree parse_production(){ // program: ident = expression
    if( next_token->type == Identifier ){
        tree result = create_node(next_token->value, ID);
        scan_token();
        if (next_token!=NULL){
            if ( next_token->type == Eql ){
                scan_token();
                list* exp = parse_expression();
                result->children = concactenate(result->children, exp);
                if (next_token != NULL){
                    if( next_token->type == SemiColon){
                        scan_token();
                        if(next_token!=NULL){
                            printf("\n error: invalid syntax");
                        }
                        else{
                            return result;
                        }
                    }
                    else{
                        printf("\nerror: invalid syntax");
                    }
                }
                else{
                    printf("\nerror: expected semicolon");
                }
            }
            else{
                printf("\nerror: expected '='");
            }
        }
        else{
            printf("\nerror: expected a production rule");
        }
    }
    else{
        printf("\nerror: expected 'Identifier'");
    }
    return NULL;
}

list* parse_expression(){
    if (next_token != NULL){
        list* a = parse_term();
        tree bar = NULL;
        while( (next_token!=NULL) && (next_token->type == Bar) ){
            bar = create_node("", ALTERNATIVE);
            bar->children = concactenate(bar->children, a);
            
            scan_token();
            list* b = parse_term();
            if (b->child != NULL){
                bar->children = concactenate(bar->children, b);
            }
            else{
                printf("\nsyntax error: expected expression");
                exit(EXIT_FAILURE);
            }
            
        }

        if(bar!=NULL && bar->children!=NULL ){
            list* BAR = init_list();
            push(BAR, bar);
            return BAR;
        }
        if (a!= NULL && bar==NULL){
            return a;
        }
    }
    else{
        printf("\nsyntax error: expected expression");
        exit(EXIT_FAILURE);
    }
}

list* parse_term(){
    list* children = init_list();
    tree a = NULL;
    while((next_token != NULL )&& 
    (( next_token->type == Identifier ) || ( next_token->type == Literal) || ( next_token->type == LPar ) || ( next_token->type == LBrak) || ( next_token->type == LBrace))){
        a = parse_factor();
        push(children, a);
    }
    return children;
}

tree parse_factor(){
    tree a = NULL;
    list* e = NULL;
    switch (next_token->type){
        case Identifier:
            a = create_node(next_token->value, ID);
            scan_token();
            return a;
            break;
        case Literal:
            a = create_node(next_token->value, LITERAL);
            scan_token();
            return a;
            break;
        case LPar:
            scan_token();
            e = parse_expression();
            if( next_token->type == RPar ){
                scan_token();
                tree b = create_node("", PARENT);
                b->children = concactenate(b->children, e);
                return b;
            }
            else{
                printf("\nsyntax error : expected ')' ");
                exit(EXIT_FAILURE);
            }
            break;
        case LBrak:
            scan_token();
            e = parse_expression();
            if( next_token->type == RBrak ){
                scan_token();
                tree b = create_node("", OPTIONAL);
                b->children = concactenate(b->children, e);
                return b;
            }
            else{
                printf("\nsyntax error : expected ']' ");
                exit(EXIT_FAILURE);
            }
            break;
        case LBrace:
            scan_token();
            e = parse_expression();
            if( next_token->type == RBrace ){
                scan_token();
                tree b = create_node("", RECURSSIVE);
                b->children = concactenate(b->children, e);
                return b;
            }
            else{
                printf("\nsyntax error : expected '}' ");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            printf("\nsyntax error : invalid factor");
            exit(EXIT_FAILURE);
            break;
    }
}
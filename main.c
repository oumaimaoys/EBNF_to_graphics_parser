#include <stdio.h>
#include <stdlib.h>
#include "C:/Users/lenovo/Documents/insea2023/compilateur/parser.h"

int main(){
    char input_ebnf[100];
    scanf("%99[^\n]", input_ebnf);

    tree parse_tree = parse_program(input_ebnf);
    read_tree(parse_tree, 0);

    return 0;
}
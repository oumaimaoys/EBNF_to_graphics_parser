#include "tree.h"

tree parse_program(char* source_code);

tree parse_expression(char* source_code);

int parse_alternatives(char* source_code);

int parse_optionals(char* source_code);

int parse_recurssives(char* source_code);

int parse_literal(char* source_code);

int parse_identifier(char* source_code);

int parse_parentheses(char* source_code);
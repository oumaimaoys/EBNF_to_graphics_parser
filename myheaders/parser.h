#ifndef PARSER_H
#define PARSER_H

#include "tree.h"

tree parser(Token* input);
tree parse_production();
list* parse_expression();
list* parse_term();
tree parse_factor();

#endif /* PARSER_H */
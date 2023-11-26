// TODO redefine type for token as enum
typedef struct Token{
    char* type;
    char* value;
    struct Token* next;
} Token;

Token* new_token(char* type, char* value);

Token* scan_token(char* input); // input 

Token* lexer(char* expression); // returns pointers to first element in list of tokens
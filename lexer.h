typedef enum {
    Identifier,
    Literal,
    LPar,
    RPar,
    LBrak,
    RBrak,
    LBrace,
    RBrace,
    Bar,
    Eql,
} TokenType;

typedef struct Token{
    TokenType type;
    char* value;
    struct Token* next;
} Token;

Token* lexer(char* expression); // returns pointers to first element in list of tokens
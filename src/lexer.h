#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_INT_KEYWORD,
    TOKEN_RETURN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_SEMICOLON,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char* lexeme;
} Token;

void initLexer(char* code);
Token getNextToken();
Token createToken(TokenType type, const char* lexeme);
#endif

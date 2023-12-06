#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* sourceCode;
int current = 0;


Token getNextToken(){
    while (sourceCode[current] != '\0'){
        char c = sourceCode[current];
        switch(c){
            case ' ':
            case '\r':
            case '\t':
            case '\n':
                current++;
                break;
            case '(':
                current++;
                return createToken(TOKEN_LEFT_PAREN, "(");
            case ')':
                current++;
                return createToken(TOKEN_RIGHT_PAREN, ")");
            case '{':
                current++;
                return createToken(TOKEN_LEFT_BRACE, "{");
            case '}':
                current ++;
                return createToken(TOKEN_RIGHT_BRACE, "}");
            case ';':
                current++;
                return createToken(TOKEN_SEMICOLON, ";");
            default:
                if(isalpha(c)){
                    int start = current;
                    while(isalpha(sourceCode[current])) current++;
                    int length = current - start;
                    char* lexeme = (char*)malloc(length + 1);
                    memcpy(lexeme, &sourceCode[start], length);
                    lexeme[length] = '\0';
                    if(strcmp(lexeme, "int") == 0){
                        return createToken(TOKEN_INT_KEYWORD, lexeme);
                    } else if(strcmp(lexeme, "return") == 0){
                        return createToken(TOKEN_RETURN_KEYWORD, lexeme);
                    } else{
                        return createToken(TOKEN_IDENTIFIER, lexeme);
                    }
                } else if (isdigit(c)){
                    int start = current;
                    while(isdigit(sourceCode[current])) current++;
                    int length = current - start;
                    char* lexeme = (char*)malloc(length + 1);
                    memcpy(lexeme, &sourceCode[start], length);
                    lexeme[length] = '\0';
                    return createToken(TOKEN_NUMBER, lexeme);
                } else{
                    printf("Error: Unrecognized character '%c'\n", c);
                    exit(EXIT_FAILURE);
                }
        }
    }
    return createToken(TOKEN_EOF, "EOF");
}

void initLexer(char* code){
    sourceCode = code;
    current = 0;
}

Token createToken(TokenType type, const char* lexeme) {
    char* lexemeCopy = malloc(strlen(lexeme) + 1);
    strcpy(lexemeCopy, lexeme);
    return (Token){type, lexemeCopy};
}

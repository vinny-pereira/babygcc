#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "lexer.h"

int fileExists(const char *path) {
    struct stat buffer;   
    return (stat(path, &buffer) == 0); 
}

char *readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Cannot allocate memory\n");
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

int main(int argc, char *argv[]){
    char *source = NULL;
    char *target = NULL;
    int opt;
    
    if (argc < 5) {
        fprintf(stderr, "Usage: %s -s sourcefile -t targetfile\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    while ((opt = getopt(argc, argv, "s:t:")) != -1) {
        switch (opt) {
            case 's':
                source = optarg;
                break;
            case 't':
                target = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s -s sourcefile -t targetfile\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (source == NULL || target == NULL) {
        fprintf(stderr, "Both source and target files must be specified.\n");
        exit(EXIT_FAILURE);
    }

    if (!fileExists(source)) {
        fprintf(stderr, "Error: Source file '%s' does not exist.\n", source);
        exit(EXIT_FAILURE);
    }

    char *sourceText = readFile(source);
    initLexer(sourceText);
    
    Token token;
    do {
        token = getNextToken();
        printf("Token: %d, Lexeme: %s\n", token.type, token.lexeme);
        free(token.lexeme); // Free the lexeme after printing
    } while (token.type != TOKEN_EOF);

    free(sourceText);
    return 0;
}

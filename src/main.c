#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int fileExists(const char *path) {
    struct stat buffer;   
    return (stat(path, &buffer) == 0); 
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

    printf("source: %s\ntarget: %s\n", source, target);

    return 0;
}

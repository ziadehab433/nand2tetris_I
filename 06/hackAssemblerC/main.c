#include <stdlib.h>
#include <stdio.h>

#include "parser.h"

int main (int argc, char **argv) { 
    if (argc != 2) { 
        perror("invalid arguemnts");
        exit(1);
    }

    char *file_name = argv[1];

    Parser *parser = (Parser *) malloc(sizeof(Parser));
    parser->file_name = file_name;

    parse_file(parser);
}

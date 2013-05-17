#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

char readArgument(int, char **);

int main(int argc, char **argv)
{

    return 0;
}

char readArgument(int argc, char **argv)
{
    if (argc == 2) {
        if (!(strcmp(argv[1], "-h"))) {
            return 'h';
        }
    }

    return '0';
}

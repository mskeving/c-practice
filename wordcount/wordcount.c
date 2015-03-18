#include <stddef.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    printf("program name: \"%s\"\n", argv[0]);

    printf("arguments:");
    for (int i = 1; i < argc; i++) {
        printf(" \"%s\"", argv[i]);
    }
    printf("\n");

    return 0;
}

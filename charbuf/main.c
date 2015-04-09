#include "charbuf.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, __attribute__((unused)) const char** argv)
{
    if (argc != 1) {
        fprintf(stderr, "Not expecting any arguments.\n");
        return 1;
    }

    charbuf buf;
    charbuf_init(&buf);
    charbuf_append(&buf, "Hello");
    charbuf_append(&buf, ", world!");

    char* r = charbuf_make_cstring(&buf);
    printf("Result: \"%s\"\n", r);
    free(r);

    charbuf_destroy(&buf);

    return 0;
}

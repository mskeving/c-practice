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
    charbuf_append(&buf, ", world! lots of junk words that are junk.");
    printf("after append: \"%s\"\n", charbuf_make_cstring(&buf));
    charbuf_prepend(&buf, "something not important. ");

    printf("after prepend: \"%s\"\n", charbuf_make_cstring(&buf));
    printf("cstring of length 38: \"%s\"\n", charbuf_make_cstring_of_length(&buf, 38));

    charbuf_truncate(&buf, 24);

    char* r = charbuf_make_cstring(&buf);
    printf("After truncate: \"%s\"\n", r);
    free(r);

    charbuf_destroy(&buf);

    return 0;
}

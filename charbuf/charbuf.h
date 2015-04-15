#ifndef INCLUDED_charbuf_h
#define INCLUDED_charbuf_h

#include <stddef.h>

struct charbuf {
    // TODOO: Declare the fields you need.
    char *data;
    size_t length;
    size_t capacity;
};

typedef struct charbuf charbuf;  // So users can say "charbuf" instead of "struct charbuf".

void charbuf_init(charbuf*);
void charbuf_destroy(charbuf*);

void charbuf_append(charbuf*, const char*);
void charbuf_prepend(charbuf*, const char*);
size_t charbuf_length(const charbuf*);
void charbuf_truncate(charbuf*, size_t new_length);
char* charbuf_make_cstring(const charbuf*);
char* charbuf_make_cstring_of_length(const charbuf*, size_t c_length);

#endif

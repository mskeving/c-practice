#ifndef INCLUDED_charbuf_h
#define INCLUDED_charbuf_h

#include <stddef.h>

struct charbuf {
    // TODO: Declare the fields you need.
};

typedef struct charbuf charbuf;  // So users can say "charbuf" instead of "struct charbuf".

void charbuf_init(charbuf*);
void charbuf_destroy(charbuf*);

void charbuf_append(charbuf*, const char*);
size_t charbuf_length(const charbuf*);
void charbuf_truncate(charbuf*, size_t new_length);
char* charbuf_make_cstring(const charbuf*);

#endif

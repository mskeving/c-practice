#include "charbuf.h"

#include <stdlib.h>
#include <string.h>

void charbuf_init(charbuf* buf)
{
    // TODO: malloc() any memory you need.  Fill in the fields of 'buf'.
    abort();
}

void charbuf_destroy(charbuf* buf)
{
    // TODO: free() any memory you allocated.
    abort();
}

void charbuf_append(charbuf* buf, const char* cstring)
{
    // TODO: You may need to allocate more memory to make room for 'cstring'.
    abort();
}

size_t charbuf_length(const charbuf* buf)
{
    // TODO: Return the length of the string in 'buf'.  This might be less than the actual
    // allocated capacity of 'buf'.
    abort();
}

void charbuf_truncate(charbuf* buf, size_t new_length)
{
    // TODO: Return the length of the string in 'buf'.  This might be less than the actual
    // allocated capacity of 'buf'.
    abort();
}

char* charbuf_make_cstring(const charbuf* buf)
{
    // TODO: Allocate memory for a new string and copy the data from 'buf' into that new
    // string.  Make sure that string
    // allocated capacity of 'buf'.
    abort();
}

#include "charbuf.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void charbuf_init(charbuf* buf)
{
    // TODOO: malloc() any memory you need.  Fill in the fields of 'buf'.
    buf->data = malloc(16);
    buf->length = 0;
    buf->capacity = 16;
}

void charbuf_destroy(charbuf* buf)
{
    // TODOO: free() any memory you allocated.
    free(buf->data);
}

void charbuf_append(charbuf* buf, const char* cstring)
{
    // TODOO: You may need to allocate more memory to make room for 'cstring'.

    size_t charCounter = strlen(cstring);

    // if not enough space, allocate memory for string twice the size until enough
    if ((buf->length + charCounter) > buf->capacity) {
        size_t newCapacity = buf->capacity*2;
        while (newCapacity < buf->length + charCounter) {
            newCapacity *= 2;
        };
        char* newData = malloc(newCapacity);
        // copy old data in
        memcpy(newData, buf->data, buf->length);
        free(buf->data);
        buf->capacity = newCapacity;
        buf->data = newData;
    }

    // copy new data in
    for (size_t i=0; i<charCounter; i++){
        buf->data[i+buf->length] = cstring[i];
    }
    buf->length += charCounter;
}

size_t charbuf_length(const charbuf* buf)
{
    // TODOO: Return the length of the string in 'buf'.  This might be less than the actual
    // allocated capacity of 'buf'.
    return buf->length;
}

void charbuf_truncate(charbuf* buf, size_t new_length)
{
    // TODOO: Return the length of the string in 'buf'.  This might be less than the actual
    // allocated capacity of 'buf'.
    if (new_length > buf->length) {
        fprintf(stderr, "Error truncating: buf is already smaller than size %lu.\n", new_length);
        abort();
    }
    if (new_length * 4 < buf->capacity) {
        buf->data = realloc(buf->data, new_length);
    }
    buf->length = new_length;
}

char* charbuf_make_cstring(const charbuf* buf)
{
    // TODOO: Allocate memory for a new string and copy the data from 'buf' into that new
    // string.  Make sure that string
    // allocated capacity of 'buf'.

    char* cstring = malloc(buf->length+1);
    memcpy(cstring, buf->data, buf->length);
    cstring[buf->length] = 0;
    return cstring;
}

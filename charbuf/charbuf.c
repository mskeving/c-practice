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

void add_capacity(charbuf* buf, const char* cstring)
{
    // allocate memory for buf->data + cstring. Do twice the size until enough
    size_t len_cstring = strlen(cstring);
    size_t new_capacity = buf->capacity*2;
    while (new_capacity < buf->length + len_cstring) {
        new_capacity *= 2;
    };

    char* new_data = malloc(new_capacity);
    memcpy(new_data, buf->data, buf->length);
    free(buf->data);
    buf->data = new_data;
    buf->capacity = new_capacity;
}

void charbuf_prepend(charbuf* buf, const char* cstring)
{
    size_t len_cstring = strlen(cstring);

    if (len_cstring + buf->length > buf->capacity) {
        add_capacity(buf, cstring);
    }

    // move current data over to make room for cstring in beginning
    for (size_t i=0; i<buf->length; i++) {
        size_t curr_position = buf->length - (1 + i);
        buf->data[curr_position+len_cstring] = buf->data[curr_position];
    }

    // insert new data into beginning indices
    for (size_t i=0; i<len_cstring; i++) {
        buf->data[i] = cstring[i];
    }
    buf->length = buf->length + len_cstring;
}

void charbuf_append(charbuf* buf, const char* cstring)
{
    // TODOO: You may need to allocate more memory to make room for 'cstring'.

    size_t len_cstring = strlen(cstring);

    if ((buf->length + len_cstring) > buf->capacity) {
        add_capacity(buf, cstring);
    }

    // copy new data in
    for (size_t i=0; i<len_cstring; i++){
        buf->data[i+buf->length] = cstring[i];
    }
    buf->length += len_cstring;
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
    // string.  Make sure that string allocated capacity of 'buf'.

    char* cstring = malloc(buf->length+1);
    memcpy(cstring, buf->data, buf->length);
    cstring[buf->length] = 0;
    return cstring;
}

char* charbuf_make_cstring_of_length(const charbuf* buf, size_t c_length)
{
    // TODOO: Allocate memory for a new string of a defined size and copy the data     
    // from 'buf' into that new string.  Make sure that string allocated capacity of 'buf'.

    char* cstring = malloc(c_length+1);
    memcpy(cstring, buf->data, c_length);
    cstring[c_length] = 0;
    return cstring;
}

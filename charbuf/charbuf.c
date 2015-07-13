#include "charbuf.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void charbuf_init(charbuf* buf)
{
    // TODOO: malloc() any memory you need.  Fill in the fields of 'buf'.
    buf->data = malloc(516);
    buf->length = 0;
    buf->capacity = 16;
    buf->start = 0;
    buf->end = 0;
}

void charbuf_destroy(charbuf* buf)
{
    // TODOO: free() any memory you allocated.
    free(buf->data);
}

static void add_capacity(charbuf* buf, const char* cstring)
{
    // allocate memory for buf->data + cstring. Do twice the size until enough
    size_t len_cstring = strlen(cstring);
    size_t new_capacity = buf->capacity*2;
    while (new_capacity < buf->length + len_cstring) {
        new_capacity *= 2;
    };

    char* new_data = malloc(new_capacity);
    if (buf->start != 0) {
        size_t len_end_data = buf->capacity - buf->start;
        memcpy(new_data, &buf->data[buf->start], buf->capacity);
        memcpy(&new_data[len_end_data], buf->data, buf->end);
        buf->end = len_end_data + buf->end;
        buf->start = 0;
    } else {
        memcpy(new_data, &buf->data[0], buf->end);
    }
    free(buf->data);
    buf->data = new_data;
    buf->capacity = new_capacity;
}

static size_t get_length(const charbuf* buf)
{
    if (buf->start == 0) {
        return buf->end;
    }

    return (buf->capacity - buf->start) + buf->end;
}

void charbuf_prepend(charbuf* buf, const char* cstring)
{
    size_t len_cstring = strlen(cstring);
    if (((buf->start == 0) && (buf->capacity-buf->length < len_cstring)) ||
            ((buf->start != 0) && (buf->start-buf->end < len_cstring))) {
        add_capacity(buf, cstring);
    }

    if (buf->start == 0) {
        memcpy(&buf->data[buf->capacity - len_cstring], cstring, len_cstring);
        buf->start = buf->capacity - len_cstring + 1;
    } else {
        memcpy(&buf->data[buf->start - len_cstring], cstring, len_cstring);
        buf->start = buf->start - len_cstring + 1;
    }
    buf->length = get_length(buf);
}

void charbuf_prepend_bad(charbuf* buf, const char* cstring)
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
    memcpy(&buf->data[buf->length], cstring, len_cstring);
    buf->end += len_cstring;
    buf->length = get_length(buf);
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
    if (buf->start == 0) {
        memcpy(cstring, buf->data, buf->length);
    } else {
        size_t len_end_data = buf->capacity - buf->start;
        memcpy(cstring, &buf->data[buf->start], buf->capacity);
        memcpy(&cstring[len_end_data], buf->data, buf->end);
    }
    cstring[buf->length] = 0;
    return cstring;
}

char* charbuf_make_cstring_of_length(const charbuf* buf, size_t offset, size_t length)
{
    // TODOO: Allocate memory for a new string of a defined size and copy the data     
    // from 'buf' into that new string.  Make sure that string allocated capacity of 'buf'.

    if (offset + length > buf->length) {
        fprintf(stderr, "Error making string of length %lu: data is not large enough. \n", length);
        abort();
    }
    char* cstring = malloc(length+1);
    if (buf->start == 0) {
        memcpy(cstring, &buf->data[offset], length);
    } else {
        size_t len_end_data = buf->capacity - buf->start;
        if (len_end_data < length) {
            memcpy(cstring, &buf->data[buf->start], buf->capacity);
            memcpy(&cstring[len_end_data], buf->data, length - len_end_data);
        } else {
            memcpy(cstring, &buf->data[buf->start], length);
        }
    }
    cstring[length] = 0;
    return cstring;
}

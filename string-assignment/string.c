#include "string.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/**
 * See string.h for function documentation. Please use the assert() function to
 * ensure that requirements are satisfied.
 */

/* Should make use of: malloc() */
void StringNew(string *s, int initialAllocation) {
    /* TODO */
}


/* Should make use of: free() */
void StringDispose(string *s) {
    /* TODO */
}


int StringLength(const string *s) {
    /* TODO */
    return -1;
}


char *StringNth(string *s, int position) {
    /* TODO */
    return NULL;
}


/* Should make use of: realloc(), memmove() */
void StringInsert(string *s, char c, int position) {
    /* TODO */
}


/* Should make use of: realloc() */
void StringAppend(string *s, char c) {
    /* TODO */
}


void StringReplace(string *s, char c, int position) {
    /* TODO */
}


/* Should make use of: memmove() */
void StringDelete(string *s, int position) {
    /* TODO */
}

/* Should make use of: bsearch(), CompareChar */
int StringSearch(const string *s, char key, int startIndex, bool isSorted) {
    /* TODO */
    return -1;
}


/* Should make use of: qsort() */
void StringSort(string *s) {
    /* TODO */
}

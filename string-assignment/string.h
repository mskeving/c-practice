/**
 * File: string.h
 * ---------------
 * Defines the interface for a resizable string.
 *
 * The string allows the client to store any number of characters, and is
 * appropriate for string editing operations. It supports efficient character
 * access and appending/inserting/deleting characters as well as optional
 * sorting and searching. In all cases, the string imposes no upper bound on
 * the number of characters and deals with all its own memory management.
 */

#ifndef _string_
#define _string_

#include "bool.h"

/**
 * Type: string
 * ------------
 *
 * Defines the concrete representation of the string. Even though everything is
 * exposed, the client should respect the the privacy of the representation and
 * initialize, dispose of, and otherwise interact with a string using only the
 * functions defined in this file.
 */

typedef struct {
  int logical_length;     // Number of bytes currently in use
  int allocated_length;   // Number of bytes that will fit in allocated memory
  char *data;             // Pointer to the raw data
} string;

/**
 * Function: StringNew
 * Usage: string limerick;
 *        StringNew(&limerick, 200);
 * -------------------
 * Constructs a newly-allocated or previously destroyed string to be the empty
 * string.
 *
 * The initialAllocation parameter specifies the initial allocated length of
 * the string. The allocated length is the number of characters for which space
 * has been allocated: the logical length is the number of those characters
 * currently being used. Since this function creates an empty string, the
 * logical length will be zero.
 *
 * The initialAllocation is the client's opportunity to reserve the appropriate
 * amount of memory for his/her particular needs. Clients who expect their
 * strings to become large should probably choose a large initial allocation
 * size, whereas clients who expect the string to be relatively small should
 * choose a smaller initialAllocation size. You want to minimize the number of
 * reallocations, but you don't want to pre-allocate all that much memory if
 * you don't expect to use very much of it. If the client passes 0 for
 * initialAllocation, the implementation will use a default value of its own
 * choosing. As assert is raised if the initialAllocation value is less than 0.
 */

void StringNew(string *s, int initialAllocation);

/**
 * Function: StringDispose
 * -----------------------
 * Frees up all the memory of the specified string.
 */

void StringDispose(string *s);

/**
 * Function: StringLength
 * ----------------------
 * Returns the logical length of the string, i.e. the number of characters
 * currently in the string. Must run in constant time.
 */

int StringLength(const string *s);

/**
 * Method: StringNth
 * -----------------
 * Returns a pointer to the character at the given position in the string.
 * Numbering begins with 0. An assert is raised if position is less than 0 or
 * greater than the logical length minus 1. Note this function returns a
 * pointer into the string's storage, so the pointer should be used with care.
 * This method must operate in constant time.
 *
 * We could have written the string without this sort of access, but it is
 * useful and efficient to offer it, although the client needs to be careful
 * when using it.  In particular, a pointer returned by StringNth becomes
 * invalid after any calls which involve insertion into, deletion from or
 * sorting of the string, as all of these may rearrange the characters to some
 * extent.
 */

char *StringNth(string *s, int position);

/**
 * Function: StringInsert
 * ----------------------
 * Inserts a single new character into the specified string, placing it at the
 * specified position. An assert is raised if position is less than 0 or
 * greater than the logical length. The characters after the supplied position
 * will be shifted over to make room. This method runs in linear time.
 *
 * If the allocated space is completely full, it will need to be increased to
 * make room for the inserted element. The realloc() function increases the
 * allocated memory at a specified address, preserving any data stored
 * there. Doubling the allocated space is a simple rule of thumb that allows
 * StringAppend() (see below) to run in amortized constant time, and more
 * generally reduces the number of expensive reallocations.
 *
 * Don't worry about using realloc() to shrink the string's allocation if a
 * bunch of characters get deleted. It turns out that many implementations of
 * realloc() don't even pay attention to such a request, so there is little
 * point in asking. Just leave the string over-allocated and no one will care.
 */

void StringInsert(string *s, char c, int position);

/**
 * Function: StringAppend
 * ----------------------
 * Appends a new character to the end of the specified string. Note that right
 * after this call, the new character will be the last in the string; i.e. its
 * position will be the logical length minus 1. This method must run in
 * constant time (neglecting the memory reallocation time which may be required
 * occasionally).
 */

void StringAppend(string *s, char c);

/**
 * Function: StringReplace
 * -----------------------
 * Overwrites the character at the specified position with a new value.  An
 * assert is raised if position is less than 0 or greater than the logical
 * length minus one.  None of the other characters are affected or rearranged
 * by this operation, and the size of the string remains constant. This method
 * must operate in constant time.
 */

void StringReplace(string *s, char c, int position);

/**
 * Function: StringDelete
 * ----------------------
 * Deletes the character at the specified position from the string.  An assert
 * is raised if position is less than 0 or greater than the logical length
 * minus one. All the characters after the specified position will be shifted
 * over to fill the gap. This method runs in linear time. It does not shrink
 * the allocated size of the string when a character is deleted; the string
 * just stays over-allocated.
 */

void StringDelete(string *s, int position);

/**
 * Function: StringSearch
 * ----------------------
 * Searches the specified string for a character that equals the character
 * passed as the key. The startIndex parameter controls where the search
 * starts. If the client desires to search the entire string, they should pass
 * 0 as the startIndex. The method will search from there to the end of the
 * string. The isSorted parameter allows the client to specify that the string
 * is already in sorted order, in which case StringSearch() uses a faster
 * binary search. If isSorted is false, a simple linear search is used.  If the
 * character is found, its position is returned; else the function returns -1.
 * Calling this function does not re-arrange or change contents of the string
 * in any way.
 *
 * An assert is raised if startIndex is less than 0 or greater than
 * the logical length (although searching from logical length will never
 * find anything, allowing this case means you can search an entirely empty
 * string from 0 without getting an assert).
 */

int StringSearch(const string *s, char key, int startIndex, bool isSorted);

/**
 * Function: StringSort
 * --------------------
 * Sorts the string into ascending order. The position of the characters will
 * change to reflect the new ordering.
 */

void StringSort(string *s);


/**
 * CompareChar
 * -----------
 * Comparator function used to compare two character elements within a string.
 * Used for both sorting and searching in the array of characters.  Has the same
 * return value semantics as the strcmp library function (negative if A<B, zero if A==B,
 * positive if A>B).
 */

static int CompareChar(const void *elemA, const void *elemB) {
    return (*(char *)elemA - *(char *)elemB);
}

#endif

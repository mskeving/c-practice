#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include <assert.h>

#define YES_OR_NO(value) (value != 0 ? "Yes" : "No")

/**
 * PrintString
 * -----------
 * Prints all of the characters in a string, one at a time. The file
 * pointer is passed as the client data, so that it can be used to
 * print to any FILE *.
 */

static void PrintString(void *fp, void *string)
{
  for (int i=0; i<StringLength(string); i++) {
    fprintf((FILE *)fp, "%c", *StringNth(string, i));
  }
  fflush((FILE *)fp);
}

/**
 * Function: TestAppend
 * --------------------
 * Appends letters of alphabet in order, then appends a few digit chars.
 * Uses StringMap to print the string contents before and after.
 */

static void TestAppend(string *alphabet)
{
  char ch;
  int i;

  for (ch = 'A'; ch <= 'Z'; ch++)   //  Start with letters of alphabet
    StringAppend(alphabet, ch);
  assert(StringLength(alphabet) == 26);

  fprintf(stdout, "First, here is the alphabet: ");
  PrintString(stdout, alphabet);
  fprintf(stdout, "\n");

  for (i = 0; i < 10; i++) {	    // Append digit characters
    ch = '0' + i;                   // convert int to ASCII digit character
    StringAppend(alphabet, ch);
  }
  assert(StringLength(alphabet) == 36);

  fprintf(stdout, "After append digits: ");
  PrintString(stdout, alphabet);
  fprintf(stdout, "\n");
}


/**
 * Function: TestSearch
 * --------------------
 * Tests the searching capability of the string by looking for specific
 * character.  Calls StringSearch twice, once to see if it finds the character
 * using a binary search (given the array is sorted) and once to see if it
 * finds the character using a linear search.  Reports results to stdout.
 */

static void TestSearch(string *v, char ch)
{
  int foundSorted, foundNot;

  foundSorted = StringSearch(v, ch, 0, true); // Test sorted
  foundNot = StringSearch(v, ch, 0, false);   // Not sorted
  fprintf(stdout,"\nFound '%c' in sorted array? %s. How about unsorted? %s.",
	  ch, YES_OR_NO((foundSorted != -1)),
	  YES_OR_NO((foundNot != -1)));
}

/**
 * Function: TestSortSearch
 * ------------------------
 * Sorts the string into alphabetic order and then tests searching
 * capabilities, both the linear and binary search versions.
 */

static void TestSortSearch(string *alphabet)
{
  StringSort(alphabet);	 // Sort into order again
  fprintf(stdout, "\nAfter sorting: ");
  PrintString(stdout, alphabet);
  TestSearch(alphabet, 'J');	// Test searching capabilities
  TestSearch(alphabet, '$');
  fprintf(stdout, "\n");
}

/**
 * Function: TestAt
 * ----------------
 * Uses StringNth to access every other letter and
 * lowercase it. Prints results using StringMap.
 */

static void TestAt(string *alphabet)
{
  int i;

  for (i = 0; i < StringLength(alphabet); i += 2) { // Lowercase every other
    char *elem = (char *) StringNth(alphabet, i);
    *elem = tolower(*elem);
  }

  fprintf(stdout, "\nAfter lowercase every other letter: ");
  PrintString(stdout, alphabet);
  fprintf(stdout, "\n");
}

/**
 * Function: TestInsertDelete
 * --------------------------
 * Inserts dashes at regular intervals, then uses delete to remove
 * them.  Makes sure that insert at allows you to insert at end of
 * array and checks no problem with deleting very last element.  It's
 * always a good idea to directly test the borderline cases to make
 * sure you have handled even the unusual scenarios.
 */

static void TestInsertDelete(string *alphabet)
{
  char ch = '-';
  int i;

  for (i = 3; i < StringLength(alphabet); i += 4) // Insert dash every 4th char
    StringInsert(alphabet, ch, i);
  fprintf(stdout, "\nAfter insert dashes: ");
  PrintString(stdout, alphabet);

  for (i = 3; i < StringLength(alphabet); i += 3) // Delete every 4th char
    StringDelete(alphabet, i);
  fprintf(stdout, "\nAfter deleting dashes: ");
  PrintString(stdout, alphabet);

  ch = '!';
  StringInsert(alphabet, ch, StringLength(alphabet));
  StringDelete(alphabet, StringLength(alphabet) - 1);
  fprintf(stdout, "\nAfter adding and deleting at the very end: ");
  PrintString(stdout, alphabet);
  fprintf(stdout, "\n");
}

/**
 * Function: TestReplace
 * ---------------------
 * Uses repeated searches to find all occurrences of a particular
 * character and then uses replace it to overwrite value.
 */

static void TestReplace(string *alphabet)
{
  int found = 0;
  char toFind = 's', toReplace = '*';

  while (found < StringLength(alphabet)) {
    found = StringSearch(alphabet, toFind, 0, false);
    if (found == -1) break;
    StringReplace(alphabet, toReplace, found);
  }

  fprintf(stdout, "\nAfter changing all %c to %c: ", toFind, toReplace);
  PrintString(stdout, alphabet);
  fprintf(stdout, "\n");
}

/**
 * Function: DeleteEverythingVerySlowly
 * ------------------------------------
 * Empties out the string in such a way that StringDelete
 * is exercised to the hilt.  By repeatedly deleting from
 * within the string, we ensure that the shifting over of
 * bytes is working properly.
 */

static void DeleteEverythingVerySlowly(string *s)
{
  char lastOriginalChar;
  fprintf(stdout, "\nErasing everything in the string by repeatedly deleting the 10th-to-last remaining character.\n");
  fflush(stdout);
  lastOriginalChar = *StringNth(s, StringLength(s) - 1);
  while (StringLength(s) >= 10) {
    StringDelete(s, StringLength(s) - 10);
    assert(lastOriginalChar == *StringNth(s, StringLength(s) -1));
  }
  fprintf(stdout, "Almost done... deleting the last 10 elements... ");
  fflush(stdout);
  while (StringLength(s) > 0) StringDelete(s, 0);
  fprintf(stdout, "and we're all done!\n");
  fflush(stdout);
}

/**
 * Function: main
 * --------------
 * Exercises the string when it stores characters.
 * Because characaters are small and don't have any
 * complicated memory requirements, this test is a
 * good starting point to see whether or not your string
 * even has a prayer of passing more rigorous tests.
 *
 * See the documentation for each of the helper functions
 * to gain a sense as to how SimpleTest works.  The intent
 * it certainly to try out all of the string operations so
 * that everything gets exercised.
 */

int main(int ignored, char **alsoIgnored)
{
  string alphabet;
  StringNew(&alphabet, 4);
  TestAppend(&alphabet);
  TestSortSearch(&alphabet);
  TestAt(&alphabet);
  TestInsertDelete(&alphabet);
  TestReplace(&alphabet);
  DeleteEverythingVerySlowly(&alphabet);
  StringDispose(&alphabet);
  return 0;
}


/**
It’s responsible for handling command-line arguments,
storing regular expression for different patterns, fetching the regular expression for the given pattern,
building a representation for the regular expression
* @author Akshay Banda
* @file search.c
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pattern.h"
#include "parse.h"



/** On the command line, which argument is the pattern. */
#define PAT_ARG 1

/** On the command line, which argument is the input file. */
#define FILE_ARG 2

/** the patterns we are dealing with */
#define PATS 8

/** The maximum length of an input line. */
#define LINE_LEN 100

/** specificied command line arguments */
#define MAX_NUM_ARGS 3

/** pattern regex strings that we deal with (local variables)*/
char *capitalized = "[ABCDEFGHIJKLMNOPQRSTUVWXYZ][abcdefghijklmnopqrstuvwxyz]+";
char *other_words = "[ABCDEFGHIJKLMNOPQRSTUVWXYZ]+|[abcdefghijklmnopqrstuvwxyz]+";
char *integers = "[+-]?[0123456789]+";
char *real_num = "[+-]?[0123456789]+?[.][0123456789]+";
char *alphanumeric = "[ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz]+[0123456789]+[ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789]*|[0123456789]+[ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz]+[ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789]*";
char *starting_w_a = "^a";
char *empty = "^$";
char *ten_char = "^..........$";

/**
* print a whole line from matching instead of token
*
* @param line the current line number
* @param str the string/line being searched
* @param len the length of the string
* @param table the completed match table for the string
* @param first check first occurence
*              for formatting purposes
*/
void printLine(int line, char const *str, int len, bool (*table)[len + 1], bool *first)
{
  for (int begin = 0; begin <= len; begin++) {
    for (int end = begin; end <= len; end++) {
      if (table[begin][end]) {
        if (!(*first)) {
          printf("\n");
        } else {
          *first = false;
        }
        printf("line %d : %s", line, str);
        return;
      }
    }
  }
}

/**
* gets the longest subtring and prints it
*
* @param line the current line number
* @param str the string/line being searched
* @param len the length of the string
* @param table the completed match table for the string
* @param checks for first occurence of a match
*              for formatting purposes
*/
void printLongSub(int line, char const *str, int len, bool (*table)[len + 1], bool *first)
{
  bool match = false;
  for (int row = 0; row <= len; row++) {
    for (int col = row; col <= len; col++) {
      if (table[row][col]) {
        if (!(*first) && !match) {
          printf("\n");
        } else {
          *first = false;
        }
        if (!match) {
          match = true;
          printf("line %d :", line);
        }
        printf(" ");
        while (col < len && table[row][col + 1]) {
          col++;
        }
        int tempRow = row;
        while (tempRow > 0 && table[tempRow - 1][col]) {
          tempRow--;
        }
        for (int i = tempRow; i < col; i++) {
          printf("%c", str[i]);
        }
        for (int i = tempRow; i <= len; i++) {
          for (int j = col; j >= 0; j--) {
            table[i][j] = false;
          }
        }
      }
    }
  }
}

/**
* Prints the whole word if the entire string is matched
*
* @param line the current line number
* @param str the string/line being searched
* @param len the length of the string
* @param table the completed match table for the string
* @param first a pointer to a boolean representing if no match has been found yet,
*              for formatting purposes
*/
void printWord(int line, char const *str, int len, bool (*table)[len + 1], bool *first)
{
  bool match = false;
  for (int row = 0; row <= len; row++) {
    for (int col = row; col <= len; col++) {
      if (table[row][col] && (!str[row - 1] || !isalpha(str[row - 1])) && (!str[col] || !isalpha(str[col]))) {
        if (!(*first) && !match) {
          printf("\n");
        } else {
          *first = false;
        }
        if (!match) {
          match = true;
          printf("line %d :", line);
        }
        printf(" ");
        for (int i = row; i < col; i++) {
          printf("%c", str[i]);
        }
      }
    }
  }
}

/**
* Entry point for the program, parses command-line arguments, builds
* the pattern and then tests it against lines of input.
*
* @param argc number of command-line arguments
* @param argv array of command-line arguments
* @return exit status for the program
*/
int main( int argc, char *argv[] )
{
  if (argc != MAX_NUM_ARGS) {
    fprintf(stderr, "usage: search <pattern> [input-file.txt]");
    return EXIT_FAILURE;
  }
  
  FILE *fp = fopen(argv[FILE_ARG], "r");
  if (!fp) {
    fprintf(stderr, "Can't open input file: %s", argv[FILE_ARG]);
  }
  
  
  char *regex[PATS] = {capitalized, other_words, integers, real_num, alphanumeric, starting_w_a, empty, ten_char};
  
  int patternLen = strlen(argv[1]);
  char *pstr;
  
  void (*report)(int line, char const *str, int len, bool (*table)[len + 1], bool *first);
  
  if (patternLen == strlen("capitalized_words") && strncmp(argv[1], "capitalized_words", strlen("capitalized_words")) == 0) {
    pstr = regex[0];
    report = printWord;
  } else if (patternLen == strlen("other_words") && strncmp(argv[1], "other_words", strlen("other_words")) == 0) {
    pstr = regex[1];
    report = printWord;
  } else if (patternLen == strlen("integers") && strncmp(argv[1], "integers", strlen("integers")) == 0) {
    pstr = regex[2];
    report = printLongSub;
  } else if (patternLen == strlen("real_numbers") && strncmp(argv[1], "real_numbers", strlen("real_numbers")) == 0) {
    pstr = regex[3];
    report = printLongSub;
  } else if (patternLen == strlen("alphanumeric") && strncmp(argv[1], "alphanumeric", strlen("alphanumeric")) == 0) {
    pstr = regex[4];
    report = printLongSub;
  } else if (patternLen == strlen("starting_with_a") && strncmp(argv[1], "starting_with_a", strlen("starting_with_a")) == 0) {
    pstr = regex[5];
    report = printLine;
  } else if (patternLen == strlen("empty_lines") && strncmp(argv[1], "empty_lines", strlen("empty_lines")) == 0) {
    pstr = regex[6];
    report = printLine;
  } else if (patternLen == strlen("ten_char_lines") && strncmp(argv[1], "ten_char_lines", strlen("ten_char_lines")) == 0) {
    pstr = regex[7];
    report = printLine;
  } else {
    fprintf(stderr, "Invalid pattern");
    fclose(fp);
    return EXIT_FAILURE;
  }
  
  
  Pattern *pat = parsePattern( pstr );

  
  char str[LINE_LEN + 2];
  int lineNum = 0;
  bool first = true;
  
  while (fgets(str, LINE_LEN + 2, fp)) {
    lineNum++;
    if (strlen(str) > LINE_LEN) {
      fprintf(stderr, "Input line too long");
      fclose(fp);
      pat->destroy(pat);
      return EXIT_FAILURE;
    }
    int len = strlen( str );
    if (str[len - 1] == '\n') {
      str[len - 1] = '\0';
      len--;
    }
    // Zero-filled array to use as our match table.
    bool (*table)[ len + 1 ] = calloc( ( len + 1 ) * ( len + 1 ), sizeof( bool ) );
    // Find matches for this pattern.
    pat->match( pat, str, len, table );
    
    // Print them out.
    report(lineNum, str, len, table, &first);
        
    free(table);
  }

  pat->destroy( pat );
  fclose(fp);

  return EXIT_SUCCESS;
}

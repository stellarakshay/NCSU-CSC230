/**
 * header file for pattern.c 
 *@author Akshay Banda
  */

#ifndef PATTERN_H
#define PATTERN_H

#include <stdbool.h>

//////////////////////////////////////////////////////////////////////
// Superclass for Patterns

/** A short name to use for the Pattern interface. */
typedef struct PatternStruct Pattern;

/**
  Structure used as a superclass/interface for a regular expression
  pattern.  There's a function pointer for an overridable method,
  match(), that reports all the places where this pattern matches a
  given string.  There's also an overridable method for freeing
  resources for the pattern.
*/
struct PatternStruct {
  /** Method for matching this pattern against a given string.  For
      each substring str[ begin ] .. str[ end - 1 ] that matches this
      pattern, this function sets table[ begin ][ end ] to true.

      @param pat pointer to the pattern being matched (essentially, a this
                 pointer).
      @param str input string in which we're finding matches.
      @param len length of str.
      @param table ( len + 1 ) x ( len + 1 ) array of booleans that
                   gets filled in with the substrings where this
                   pattern matches the string.
  */
  void (*match)( Pattern *pat, char const *str, int len, bool (*table)[ len + 1 ] );

  /** Free memory for this pattern, including any subpatterns it contains.
      @param pat pattern to free.
  */
  void (*destroy)( Pattern *pat );
};

/**
  Make a pattern for a single, non-special character, like `a` or `5`.

  @param sym The symbol this pattern is supposed to match.
  @return A dynamically allocated representation for this new pattern.
*/
Pattern *makeLiteralPattern( char sym );

/**
  Make a pattern for the concatenation of patterns p1 and p2.  It
  should match anything that can be broken into two substrings, s1 and
  s2, where the p1 matches the first part (s1) and p2 matches the
  second part (s2).

  @param p1 Subpattern for matching the first part of the string.
  @param p2 Subpattern for matching the second part of the string.
  @return A dynamically allocated representation for this new pattern.
*/
Pattern *makeConcatenationPattern( Pattern *p1, Pattern *p2 );

/**
* Make a StartOfPattern, a specialization of a Pattern.
*
* @return a dynamically allocated representation for this new pattern
*/
Pattern *makeStartOfPattern();

/**
* Make a End Pattern, a specialization of a Pattern.
*
* @return a dynamically allocated representation for this new pattern
*/
Pattern *makeEndOfPattern();

/**
 * pattern with single occurence of char
 * @return A dynamically allocated representation for this new pattern.
*/ 
Pattern *makeSingleOccurencePattern();

/**
 * pattern with multiple occurence of char
 * @param class character class b/w brackets
 * @return A dynamically allocated representation for this new pattern.
*/ 
Pattern *makeCharacterClassPattern( char * class );

/**
  Make a pattern for the repitition of patterns p1 which contains * symbol

  @param p1 Subpattern for matching the first part of the string.
  @return A dynamically allocated representation for this new pattern.
*/
Pattern *makeStarPattern( Pattern *p1);

/**
  Make a pattern for the repitition of patterns p1 which contains ? symbol

  @param p1 Subpattern for matching the first part of the string.
  @return A dynamically allocated representation for this new pattern.
*/
Pattern *makeQuestionPattern( Pattern *p1);

/**
  Make a pattern for the repitition of patterns p1 which contains + symbol

  @param p1 Subpattern for matching the first part of the string.
  @return A dynamically allocated representation for this new pattern.
*/
Pattern *makePlusPattern( Pattern *p1);

/**
  Make a pattern for the alernation of patterns p1 and p2.  

  @param p1 Subpattern for matching the first part of the string.
  @param p2 Subpattern for matching the second part of the string.
  @return A dynamically allocated representation for this new pattern.
*/
Pattern *makeAlternationPattern( Pattern *p1, Pattern *p2 );



#endif

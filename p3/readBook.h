/**
* This component will read the input file (book)
* and present the most relevant genre(s)
* based on words in the genre word lists
* @author Akshay Banda
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdbool.h>

/** error value for invalid input*/
#define EXIT_FAILURE 1
/** maximum amount of lines/words for a file*/
#define MAX_LINES 5000
/** maximum length of a string*/
#define MAX_WORD_LENGTH 20
/** length of array which holds percent values*/
#define PERCENT_ARRAY_LENGTH 5
/** used for calculating percent*/
#define PERCENT 100

/** percent value of tragedy genre*/
double tPercent;
/** percent value of science genre*/
double sPercent;
/** percent value of adventure genre*/
double aPercent;
/** percent value of politics genre*/
double pPercent;
/** percent value of fantasy genre*/
double fPercent;


/**
* reads the input file and accordingly equates each word to a
genre - disregards words outside of the 5 genres.
* @param book input file stream
* @param genre1Storage storage of tragic genre words
* @param genre2Storage storage of science genre words
* @param genre3Storage storage of politics genre words
* @param genre4Storage storage of adventure genre words
* @param genre5Storage storage of fantasy genre words
* @param line1 number of lines(words) in tragic genre storage
* @param line2 number of lines(words) in science genre storage
* @param line3 number of lines(words) in politics genre storage
* @param line4 number of lines(words) in adventure genre storage
* @param line5 number of lines(words) in fantasy genre storage
*/
void readBookWords(FILE *book, char genre1Storage[][MAX_WORD_LENGTH],
char genre2Storage[][MAX_WORD_LENGTH], char genre3Storage[][MAX_WORD_LENGTH], char genre4Storage[][MAX_WORD_LENGTH], char genre5Storage[][MAX_WORD_LENGTH], int line1, int line2, int line3, int line4, int line5);

/** prints the most abundant genre in the book
 * if tie, prints multiple
 * @param genreWordPercent array of the given percents
*/
void identifyAndPrintGenre(double genreWordPercent[]);



/**
 * the model of the program
 * @author Akshay Banda
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** Maximum length of a book or salesperson unique id. */
#define MAX_ID 5

/** Maximum length of a book or salesperson name. */
#define MAX_NAME 30
/** initial capcity of array*/
#define INITIAL_CAPACITY 30
/** max length of line*/
#define MAX_LINE_LENGTH 100

/** Representation for a book. */
typedef struct {
  /** Unique ID for this book, containing no whitespace */
  char id[ MAX_ID + 1 ];

  /** Name of this book (maybe not unique, and maybe with whitespace). */
  char name[ MAX_NAME + 1 ];

  /** Number of books sold. */
  int sold;
  
} Book;

/** Node for linked list of books. */
struct BookNodeStruct {
  
  /** Book pointer */
  Book *book;

  /** Number of books sold */
  int sold;

  /** Pointer to the next node. */
  struct BookNodeStruct *next;
};

// A short type name to use for a node.
typedef struct BookNodeStruct BookNode;

/** Representation for a salesperson in the group. */
typedef struct {
  /** Unique ID for this salesperson (containing no whitespace). */
  char id[ MAX_ID + 1 ];

  /** Name for this salesperson (maybe not unique and maybe whitespace). */
  char name[ MAX_NAME + 1 ];

  /** List of all books sold by salesperson. */
  BookNode *head;

  /** Total number of books sold. */
  int sold;
  
} Salesperson;

/** Representation for the whole group, containing a resizable list of books
    and a resizable list of salespersons. */
typedef struct {

  /** List of all books. */
  Book **bList;

  /** Capacity of the bList array. */
  int bCap;

  /** Number of books. */
  int bCount;
  
  /** List of all the salespersons. */
  Salesperson **sList;
  
  /** Capacity of the current sList array. */
  int sCap;

  /** Number of salespersons. */
  int sCount;
} Group;

/**
 * dynamically allocates an instance of Book, initializes its fields and returns a pointer to it. 
 * @param id given id to copy into
 * @param name given name to copy into
 * @return pointer to the Book created
*/
Book *createBook( char const *id, char const *name );

/**
 * frees memory for the given book
 * @param book given book
*/
void freeBook( Book *book );

/**
 * dynamically allocates an instance of Salesperson, initializes its fields and returns a pointer to it
 * @param id given id
 * @param name given name
 * @return pointer to the Salesperson created
*/
Salesperson *createSalesperson( char const *id, char const *name );

/**
 * frees the memory used for the given salesperson
 * @param salesperson given salesperson
*/
void freeSalesperson( Salesperson *salesperson );

/**
 * dynamically allocates an instance of Group, initializes its fields and returns a pointer to it
 * @return pointer to a created group
*/
Group *createGroup();

/**
 * frees the memory used for the given group
 * @param group given group
*/
void freeGroup( Group *group );

/**
 * Given a group and a book ID, this function returns a pointer to the book with that ID, or NULL if it doesn't exist.
 * @param group given group
 * @param id given id
 * @return pointer to a book
*/
Book *getBook( Group *group, char const *id );

/**
 * Given a group and a salesperson ID, this function returns a pointer to the salesperson with that ID, or NULL if it doesn't exist.
 * @param group given group
 * @param id given id
 * @return pointer to a salesperson
*/
Salesperson *getSalesperson( Group *group, char const *id );


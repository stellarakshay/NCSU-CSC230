/** deals with the commands entered by the user*/


#include "model.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * reads a user command from standard input and performs that command, updating or using the given group instance as necessary
 * @param group given group
 * @return bool false if invalid command
*/
bool processCommand( Group *group );


/**
    Used for qsort for sorting the Salesperson list by name
    @param
s1, s2: Two Salesperson instances passed as void pointers. Converted inside function
  */
int compSalesperson(const void *s1,const void *s2);


/**
    Used for qsort for sorting the Book list by name
    @param
c1, c2: Two book instances passed as void pointers. Converted inside function
  */
int compBook(const void *b1,const void *b2);

/**
    Calls qsort on the Group to sort cList
    @param
Group *group: The instance of Group to be sorted
  */
void sortGroupBooks(Group *group);

/**
    Calls qsort on the Group to sort sList
    @param
Group *group: The instance of Group to be sorted
  */
void sortGroupSalespersons(Group *group);

/**
 * Checks if the linked list of book nodes 
 * contains a specific book with given id
 * @param head pointer to the head node of the linked list
 * @param bID the given book id
 * @return true if it contains the booknode
*/
bool contains(BookNode *head, char * bID);
/**
 * inserts a booknode into the linkedlist of books
 * owned by a salesperson with given book and boxes
 * @param head pointer to the head node of the linked list
 * @param given book struct
 * @param given number of boxes sold
 * @return the booknode inserted
*/
void insert( BookNode **head, Book *c , int val);

/**
    Used for sorting the BookNode LinkedList for Salesperson
    @param
c1, c2: Two book instances passed as void pointers. Converted inside function
  */
int compBook2(const Book *book1, const Book *book2);

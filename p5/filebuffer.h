/**
 * Deals with the bitbuffer and making file out of it
 * @author Akshay
 */

#ifndef _BITBUFFER_H_
#define _BITBUFFER_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** starting bits for bitbuffer */
#define START_CAP 4

/** Representation of a resizable array of bytes, with functions to
    make it easy to access individual bits. */
typedef struct {
  /** Resizable array of bytes stored in this buffer. */
  unsigned char *data;

  /** Number of bits currently stored in the data array (may not
      always be a multiple of 8). */
  int bitCount;

  /** Capacity of the data array, measured in bytes. */
  int cap;
} FileBuffer;

/**
* This function will dynamically allocate a new bit buffer, 
* initialize it to empty and return it to the caller.
* @return ne bit buffer
*/
FileBuffer *makeFileBuffer();
/**
 * This function will free any resources used by the given bit buffer.
 * @param buffer given bitbuffer
*/
void freeFileBuffer( FileBuffer *buffer );

/**
 * This function will return the number of bits currently stored in the given buffer.
 * @param buffer given bitbuffer
 * @return number of bits
*/
int getBitCount( FileBuffer const *buffer );

/**
 * This function will return either 0 or 1 based on the bit at the given index (idx) in buffer
 * @param given buffer
 * @param given index
 * @return true or false
*/
bool getBit( FileBuffer const *buffer, int idx );

/**
 * This function will set the bit at the given index to the given value (either zero or one).
 * @param given buffer
 * @param given index
 * @param given value
*/
void setBit( FileBuffer const *buffer, int idx, bool value );

/**
 * This function adds a bit to the end of the given bit buffer, resizing its data array if necessary.
 * @param given buffer
 * @param given value
*/
void appendBit( FileBuffer *buffer, bool value );

/**
 * This function reads an input file, 
 * stores its contents it in the data array of a new bit buffer
 * and returns it to the caller.
 * @param filename given file name
 * @return bit version of file
*/
FileBuffer *loadFileBuffer( char const *filename );

/**
 * This function saves the contents of the given bit buffer to a (binary) file with the given name. 
 * @param filename given file name
 * @param given buffer
 * @param bytes the number of bytes read in from the input file
*/
void saveFileBuffer( FileBuffer *buffer, char const *filename, int bytes );

#endif
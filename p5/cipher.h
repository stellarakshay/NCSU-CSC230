/** header file for the cipher component. 
Responsible for reading the cipher file and storing all 
the cipher in some representation that's easy to work with
 * @author Akshay
 */

#ifndef _CIPHER_H_
#define _CIPHER_H_

/** High order bits */
#define FIRST 0xFF000000

/** Second high order bits */
#define SECOND 0x00FF0000

/** Third high order bits */
#define THIRD 0x0000FF00

/** Number four*/
#define FOUR 4

/** Number two */
#define TWO 2

/** Number of bits in a byte.  */
#define BBITS 8

/** Maximum number of bits in a cipher. */
#define CIPHER_MAX 24

/** Number of bit offset */
#define BIT_OFFSET 32

/** High order bit in a byte */
#define HIGH_ORDER 128

/** Number of ASCII Cipher */
#define NUMBER_OF_LINES 256

/** ASCII Cipher for new line */
#define NEWLINE_CIPHER 10

/** Return value from lookupCipher() indicating that the given
  * string is the prefix of a cipher (so, it needs more bits
  * to match a cipher exactly. */
#define CIPHER_PREFIX -1

/** Return value from lookupCipher() indicating that the given
  * string doesn't match (and isn't a prefix of) any cipher.  This
  * should only happen in case of an error. */
#define CIPHER_INVALID -2

/** cipher that are read from a file*/
char** cipher;

/** cipher check*/
int cipherbool;

/** Given a string of '0' and '1' characters representing string of bits,
  * report whether this sequence of bits matches the cipher for any
  * byte.
  * @param bits String containing a sequence of '0' and '1'.
  * @return the byte value for a matching cipher, or values CIPHER_PREFIX
  * or CIPHER_INVALID described above. */
int lookupCipher( char const *bits );

/**
 * This function reads the cipher file and stores it in your chosen representation.
 * @param filename pointer to name of file
*/
void loadCipher( char const *filename );

/**
 * This function gives the cipher component a chance to free any resources it's using to keep up with all the cipher. 
*/
void freeCipher();

/**
 *This function returns a string representing the variable-length cipher for the given byte value. 
 * @param byte given byte value
 * @return string representing thr byte value
*/
char const *getCipher( unsigned char byte );



#endif

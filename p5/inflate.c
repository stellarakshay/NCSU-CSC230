#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filebuffer.h"
#include "cipher.h"
/**
 * Inflates given file
 * @param argc number of cl arguments
 * @param argv array of cl arguments
*/
int main(int argc, char *argv[] ) {
    if (argc != FOUR) {
        fprintf(stderr, "usage: deflate <code-file> <infile> <outfile>\n");
        return 1;
    }
    loadCipher(argv[1]);
    FILE *binfile = fopen(argv[TWO], "r");
    if (binfile == NULL) {
        perror(argv[TWO]);
        return 1;
    }
    FILE *outfile = fopen(argv[TWO + 1], "w");
    FileBuffer *buffer = loadFileBuffer(argv[TWO]);
    fclose(binfile);
    int bytes = 0;
    bytes = bytes | buffer->data[0];
    bytes = bytes << BBITS;
    bytes = bytes | buffer->data[1];
    bytes = bytes << BBITS;
    bytes = bytes | buffer->data[TWO];
    bytes = bytes << BBITS;
    bytes = bytes | buffer->data[TWO + 1];
    int foundCipher = 0;
    int lookup = 0;
    int currentBit = BIT_OFFSET;
    char* currentCode = malloc(sizeof(char) * CIPHER_MAX + 1);
    memset(currentCode, 0, CIPHER_MAX + 1);
    int index = 0;
    int codecounter = 0;
    while (foundCipher != bytes) {
        while (index < CIPHER_MAX) {
            if (getBit(buffer, currentBit))
                currentCode[index] = '1';
            else
                currentCode[index] = '0';
                codecounter++;
            index = index + 1;
            currentBit = currentBit + 1;
            lookup = lookupCipher(currentCode);
            if (lookup >= 0) {
                fprintf(outfile, "%c", lookup);
                foundCipher++;
                break;
            }
            if (codecounter == (getBitCount(buffer) - BIT_OFFSET) && foundCipher != bytes) {
                fprintf(stderr, "Invalid input file: %s\n", argv[TWO]);
                exit(EXIT_FAILURE);
            }
        }
        memset(currentCode, 0, CIPHER_MAX);
        index = 0;
    }
    free(currentCode);
    fclose(outfile);
    return 0;
}

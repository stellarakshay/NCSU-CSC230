#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filebuffer.h"
#include "cipher.h"

/**
 * Deflates given file
 * @param argc number of cl arguments
 * @param argv array of cl arguments
*/
int main(int argc, char *argv[] ) {
    if (argc != FOUR) {
        fprintf(stderr, "usage: deflate <code-file> <infile> <outfile>\n");
        return 1;
    }
    FILE *charfile = fopen(argv[TWO], "r");
    if (charfile == NULL) {
        perror(argv[TWO]);
        return 1;
    }
    FileBuffer *buffer = makeFileBuffer();
    loadCipher(argv[1]);
    unsigned char current = fgetc(charfile);
    int bytes = 0;
    while (!feof(charfile)) {
        char *cipher = (char*) getCipher(current);
        int index = 0;
        int size = strlen(cipher);
        while (index < size) {
            if (cipher[index] == '1') {
                appendBit(buffer, 1);
            }
            else if (cipher[index] == '0') {
                appendBit(buffer, 0);
            }
            index++;
        }
        current = fgetc(charfile);
        bytes++;
    }
    fclose(charfile);
    saveFileBuffer(buffer, argv[TWO + 1], bytes);
    freeCipher();
    freeFileBuffer(buffer);
    return 0;
}

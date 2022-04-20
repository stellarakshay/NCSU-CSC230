#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cipher.h"

int lookupCipher( char const *bits )
{
    for (int i = 0; i < NUMBER_OF_LINES; i++) {
        if (strcmp(cipher[i], bits) == 0)
            return i;
        
    }
    return CIPHER_INVALID;
}

void freeCipher()
{
    free(*cipher);
    free(cipher);
}

void loadCipher( char const *filename )
{
    FILE *fp;
    fp = fopen(filename, "r");
    cipher = malloc(sizeof(char*) * NUMBER_OF_LINES);
    for (int i = 0; i < NUMBER_OF_LINES; i++) {
        cipher[i] = malloc(sizeof(char) * CIPHER_MAX + TWO);
        memset(cipher[i], 0, CIPHER_MAX + 1);
        fgets(cipher[i], CIPHER_MAX + TWO, fp);
        if (strlen(cipher[i]) > CIPHER_MAX) {
            fprintf(stderr, "Invalid code file: %s\n", filename);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < strlen(cipher[i]) - 1; j++) {
            if (cipher[i][j] != '0' && cipher[i][j] != '1') {
                fprintf(stderr, "Invalid code file: %s\n", filename);
                exit(EXIT_FAILURE);
            }
        }
        cipher[i][strlen(cipher[i]) - 1] = '\0';
    }
    fclose(fp);
    for (int i = 0; i < NUMBER_OF_LINES; i++) {
        for (int j = 0; j < NUMBER_OF_LINES; j++) {
            int different = 0;
            for (int k = 0; k < strlen(cipher[j]); k++) {
                if (i == j)
                    different = 1;
                if (cipher[i][k] != cipher[j][k]) {
                    different = 1;
                }
            }
            if (!different) {
                fprintf(stderr, "Invalid code file: %s\n", filename);
                exit(EXIT_FAILURE);
            }
        }
    }
}

char const *getCipher( unsigned char byte )
{
    return cipher[byte];
}

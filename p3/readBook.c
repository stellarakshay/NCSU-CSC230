#include "readBook.h"
#include "wordLists.h"

void readBookWords(FILE *book, char genre1Storage[][MAX_WORD_LENGTH],
char genre2Storage[][MAX_WORD_LENGTH], char genre3Storage[][MAX_WORD_LENGTH], char genre4Storage[][MAX_WORD_LENGTH], char genre5Storage[][MAX_WORD_LENGTH], int line1, int line2, int line3, int line4, int line5)
{
    char word[MAX_WORD_LENGTH + 1];
    int i = 0;
    int tCount = 0;
    int sCount = 0;
    int pCount = 0;
    int aCount = 0;
    int fCount = 0;
    while(fscanf(book, "%s", word) != EOF) {
        
        if(i > MAX_LINES - 1) {
            printf("Too many words");
            exit(EXIT_FAILURE);
        }
        
        for (int p = 0, q; word[p] != '\0'; ++p) {

            // enter the loop if the character is not an alphabet
             // and not the null character
            while (!(word[p] >= 'a' && word[p] <= 'z') && !(word[p] >= 'A' && word[p] <= 'Z') && !(word[p] == '\0') && !(word[p] == '\'')) {
                for (q = p; word[q] != '\0'; ++q) {

                    // if jth element of line is not an alphabet,
                    // assign the value of (j+1)th element to the jth element
                    word[q] = word[q + 1];
                }
                word[q] = '\0';
            }
        }
        
        if(strlen(word) > MAX_WORD_LENGTH) {
            continue;
        } else {
            for(int j = 0; j < line1; j++) {
                if(strcasecmp(genre1Storage[j], word) == 0 && word[0] != '\0') {
                    
                    tCount++;
                    i++;    
                }
            }
            for(int k = 0; k < line2; k++) {
                if(strcasecmp(genre2Storage[k], word) == 0 && word[0] != '\0') {
                    
                    sCount++;
                    i++;    
                }
            }
            for(int l = 0; l < line3; l++) {
                if(strcasecmp(genre3Storage[l], word) == 0 && word[0] != '\0') {
                    
                    pCount++;
                    i++;    
                }
            }
            for(int m = 0; m < line4; m++) {
                if(strcasecmp(genre4Storage[m], word) == 0 && word[0] != '\0') {
                    
                    aCount++;
                    i++;    
                }
            }
            for(int n = 0; n < line5; n++) {
                if(strcasecmp(genre5Storage[n], word) == 0 && word[0] != '\0') {
                    
                    fCount++;
                    i++;    
                }
            }

        }
    }
    
    tPercent = ((double) tCount/i) * PERCENT;
    sPercent = ((double) sCount/i) * PERCENT;
    pPercent = ((double) pCount/i) * PERCENT;
    aPercent = ((double) aCount/i) * PERCENT;
    fPercent = ((double) fCount/i) * PERCENT;
    
    
    
    
    
}






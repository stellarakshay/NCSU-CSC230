#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "filebuffer.h"
#include "cipher.h"

FileBuffer *makeFileBuffer()
{
    FileBuffer *buff = malloc(sizeof(FileBuffer));
    buff->data = calloc(FOUR, sizeof(unsigned char*) * FOUR);
    buff->bitCount = 0;
    buff->cap = FOUR;
    return buff;
}

void freeFileBuffer( FileBuffer *buffer )
{
    free(buffer->data);
    buffer->bitCount = 0;
    buffer->cap = FOUR;
    free(buffer);
}

int getBitCount( FileBuffer const *buffer )
{
    return buffer->bitCount;
}

bool getBit( FileBuffer const *buffer, int idx )
{
    int newIdx = idx / BBITS;
    int mod = (BBITS - 1) - (idx % BBITS);
    unsigned char bits = buffer->data[newIdx];
    return (bits >> mod) & 1;
}

void setBit( FileBuffer const *buffer, int idx, bool value )
{
     if (getBit(buffer, idx) == value)
      return;
    int newIdx = idx / BBITS;
    int mod = (BBITS - 1) - (idx % BBITS);
    int number = 1;
    for (int i = 0; i < mod; i++)
      number *= TWO;
    unsigned char bits = buffer->data[newIdx];
    bits = bits ^ number;
    buffer->data[newIdx]  = bits;
    
}

void appendBit( FileBuffer *buffer, bool value )
{
    if (buffer->bitCount == (buffer->cap * BBITS)) {
        buffer->cap *= TWO;
        buffer->data = (unsigned char*)realloc(buffer->data, buffer->cap);
        for (int i = buffer->cap / TWO; i < buffer->cap; i++) {
            buffer->data[i] = 0;
        }
    }
    if (value == 0) {
        buffer->bitCount = buffer->bitCount + 1;
    } else {
        int newIdx = buffer->bitCount / BBITS;
        int mod = (BBITS - 1) - (buffer->bitCount % BBITS);
        int number = 1;
        for (int i = 0; i < mod; i++)
          number *= TWO;
        unsigned char bits = buffer->data[newIdx];
        bits = bits ^ number;
        buffer->data[newIdx] = bits;
        buffer->bitCount = buffer->bitCount + 1;
    }
}

FileBuffer *loadFileBuffer( char const *filename )
{
    FILE *fp;
    fp = fopen(filename, "r");
    unsigned char c = fgetc(fp);
    FileBuffer *buffer = makeFileBuffer();
    int counter = 0;
    int i = 0;
    while (!feof(fp)) {
        buffer->data[counter] = 0;
        while (i < BBITS) {
            appendBit(buffer, c & HIGH_ORDER);
            c = c << 1;
            i++;
        }
    i = 0;
    c = fgetc(fp);
    counter++;
    }
    fclose(fp);
    return buffer;
}

void saveFileBuffer( FileBuffer *buffer, char const *filename, int bytes )
{
    FILE *fp;
    fp = fopen(filename, "w+");
    //int i = 0;
    while (buffer->bitCount % BBITS != 0) {
      appendBit(buffer, 0);
    }
    fputc((bytes & FIRST) >> CIPHER_MAX, fp);
    fputc((bytes & SECOND) >> (BBITS * TWO), fp);
    fputc((bytes & THIRD) >> BBITS, fp);
    fputc(bytes & 0x000000FF, fp);
    fwrite(buffer->data, sizeof(unsigned char), buffer->bitCount / BBITS, fp);
    fclose(fp);
}

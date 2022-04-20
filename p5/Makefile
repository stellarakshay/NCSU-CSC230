CC = gcc
CFLAGS = -Wall -std=c99

all: deflate inflate 

inflate: cipher.o filebuffer.o
deflate: cipher.o filebuffer.o

inflate.o: cipher.h filebuffer.h
deflate.o: cipher.h filebuffer.h
cipher.o: cipher.h 
filebuffer.o: filebuffer.h


clean:
	rm -f cipher.o filebuffer.o inflate.o deflate.o
	rm -f inflate deflate
	rm -f output.txt 
	rm -f stderr.txt

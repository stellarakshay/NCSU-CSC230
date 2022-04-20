CC = gcc
CFLAGS = -Wall -std=c99

tellBookGenre: readBook.o wordLists.o

tellBookGenre.o: readBook.h 
readBook.o: readBook.h wordLists.h
wordLists.o: wordLists.h


clean:
	rm -f tellBookGenre.o readBook.o wordLists.o
	rm -f tellBookGenre
	rm -f output.txt 
	rm -f stderr.txt

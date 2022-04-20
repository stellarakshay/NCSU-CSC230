CC = gcc
CFLAGS = -Wall -std=c99



search: parse.o pattern.o


search.o: parse.h pattern.h
parse.o: parse.h pattern.h
pattern.o: pattern.h


clean:
	rm -f parse.o pattern.o search.o 
	rm -f search 
	rm -f output.txt 
	rm -f stderr.txt

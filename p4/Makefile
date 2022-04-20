CC = gcc
CFLAGS = -Wall -std=c99

tracker: command.o model.o

tracker.o: command.h 
command.o: command.h model.h
model.o: model.h


clean:
	rm -f tracker.o command.o model.o
	rm -f tracker
	rm -f output.txt 
	rm -f stderr.txt

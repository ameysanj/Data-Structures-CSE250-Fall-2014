# Makefile for the print tree assignment

OBJS = term_control.o error_handling.o main.o SplayTree.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -pedantic $(DEBUG)
LFLAGS = -Wall $(DEBUG)

programs: main

main: $(OBJS)
	$(CC) $(LFAGS) $(OBJS) -o splaydriver

main.o: main.cpp SplayTree.h term_control.h error_handling.h
	$(CC) -c $(CFLAGS) main.cpp

SplayTree.o: SplayTree.h SplayTree.cpp
	$(CC) -c $(CFLAGS) SplayTree.cpp

error_handling.o : term_control.o error_handling.h error_handling.cpp
	$(CC) -c $(CFLAGS) error_handling.cpp

term_control.o : term_control.h term_control.cpp
	$(CC) -c $(CFLAGS) term_control.cpp

clean:
	rm -f *.o a.out splaydriver

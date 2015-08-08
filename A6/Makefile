# Makefile for the UBList assignment

OBJS = term_control.o error_handling.o UBList.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -pedantic -ansi $(DEBUG)
LFLAGS = -Wall $(DEBUG)

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o listmanip

main.o: main.cpp error_handling.h UBList.h term_control.h
	$(CC) -c $(CFLAGS) main.cpp

# UBList makes use of error handling routines
UBList.o: error_handling.o UBList.h UBList.cpp
	$(CC) -c $(CFLAGS) UBList.cpp

# error handling routines make use of terminal control routines
error_handling.o : term_control.o error_handling.h error_handling.cpp
	$(CC) -c $(CFLAGS) error_handling.cpp

# this object file is at the "lowest level"
term_control.o : term_control.h term_control.cpp
	$(CC) -c $(CFLAGS) term_control.cpp

clean:
	rm -f *.o a.out listmanip

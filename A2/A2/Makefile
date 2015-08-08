OBJS = term_control.o error_handling.o Lexer.o algos.o main.o 
CC = g++
DEBUG = -g
CFLAGS = -Wall -pedantic $(DEBUG)

edgecount: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o edgecount

main.o: error_handling.h term_control.h main.cpp
	$(CC) -c $(CFLAGS) main.cpp

algos.o: algos.h algos.cpp
	$(CC) -c $(CFLAGS) algos.cpp

Lexer.o: error_handling.h term_control.h Lexer.h Lexer.cpp
	$(CC) -c $(CFLAGS) Lexer.cpp

error_handling.o : term_control.o error_handling.h error_handling.cpp
	$(CC) -c $(CFLAGS) error_handling.cpp

term_control.o : term_control.h term_control.cpp
	$(CC) -c $(CFLAGS) term_control.cpp
	
clean:
	rm -f *.o a.out *.exe edgecount

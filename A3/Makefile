OBJS = term_control.o error_handling.o Lexer.o browser.o cmd.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -pedantic -ansi -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

browser: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o browser

browser.o: browser.cpp cmd.h term_control.h error_handling.h Lexer.h
	$(CC) $(CFLAGS) browser.cpp

cmd.o: cmd.h cmd.cpp Lexer.h term_control.h error_handling.h
	$(CC) $(CFLAGS) cmd.cpp

Lexer.o: Lexer.h Lexer.cpp
	$(CC) $(CFLAGS) Lexer.cpp

error_handling.o: error_handling.h error_handling.cpp
	$(CC) $(CFLAGS) error_handling.cpp

term_control.o: term_control.h term_control.cpp
	$(CC) $(CFLAGS) term_control.cpp

clean:
	rm -rf *~ *.o browser

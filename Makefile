CC = g++
STD = c++11

CFLAGS = -Wall -g

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRCS = main.cpp game.cpp room.cpp exception.cpp

OBJS = $(SRCS:.c=.o)

MAIN = pusoy_dos


.PHONY: depend clean

all:    $(MAIN)
		@echo  Done compiling Pusoy Dos Game

$(MAIN): $(OBJS) 
		$(CC) -std=$(STD) $(CFLAGS) -o $(MAIN) $(OBJS) $(LIBS)
.c.o:
		$(CC) $(CFLAGS) -c $<  -o $@

clean:
		$(RM) *.o *~ $(MAIN)
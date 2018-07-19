CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -O2
OBJS=list.o dlist.o tree.o main.o
INCLUDE=constants.h

.PHONY: all clean

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

main.o: main.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $<

list.o: list.c list.h
	$(CC) $(CFLAGS) -c $<

dlist.o: dlist.c dlist.h
	$(CC) $(CFLAGS) -c $<

tree.o: tree.c tree.h $(INCLUDE)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) main

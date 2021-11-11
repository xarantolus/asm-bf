CC=gcc

CFLAGS=-Werror -Wall

all: abf
abf: main.c bf/bf.S bf/bf.h
	$(CC) $(CFLAGS) -o $@ $^

debug: main.c bf/bf.S bf/bf.h
	$(CC) $(CFLAGS) -g -o $@ $^

clean:
	rm -f abf


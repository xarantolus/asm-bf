CC=gcc

CFLAGS=-Werror -Wall

INTERPRETER_FILES=main.c bf/errors.c bf/bf.S bf/bf.h

all: abf
abf: $(INTERPRETER_FILES)
	$(CC) $(CFLAGS) -o $@ $^

debug: $(INTERPRETER_FILES)
	$(CC) $(CFLAGS) -g -o $@ $^

clean:
	rm -f abf


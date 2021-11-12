CC=gcc

CFLAGS=-Werror -Wall

INTERPRETER_FILES=main.c bf/errors.c bf/bf.S bf/bf.h file/reader.c file/errors.c cmdline/options.c

all: abf
abf: $(INTERPRETER_FILES)
	$(CC) $(CFLAGS) -o $@ $^

debug: $(INTERPRETER_FILES)
	$(CC) $(CFLAGS) -g -o $@ $^

clean:
	rm -f abf debug

install: abf
	cp ./abf /usr/bin/abf

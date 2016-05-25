CC=clang
CFLAGS=-Wall -Wextra -pedantic -Werror $(DEBUG) -I src/
TESTS:=$(patsubst tests/%.c, build/test_%, $(wildcard tests/*.c))
OBJECTS:=$(patsubst src/%.c, build/%.o, $(wildcard src/*.c))

all: huffman

huffman: main
	@./main

main: $(OBJECTS)

#huffman: LDFLAGS=$(wildcard build/*.o)

test: $(OBJECTS) $(TESTS)
	@bash ./tests/run.sh

test: DEBUG=-DDEBUG

build/%.o: src/%.c src/*.h build/
	$(CC) $(CFLAGS) -c $< -o $@

build/test_%: tests/%.c src/*.c src/*.h build/
	$(CC) $(CFLAGS) $< $(OBJECTS) -o $@

build/:
	mkdir $@

clean:
	rm -rf build/
	rm -rf *.dSYM
	rm -f tests/test.log

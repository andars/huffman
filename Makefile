CC=clang
CFLAGS=-Wall -Wextra -pedantic -Werror
TESTS:=$(patsubst tests/%.c, build/test_%, $(wildcard tests/*.c))
OBJECTS:=$(patsubst src/%.c, build/%.o, $(wildcard src/*.c))

all: huffman

run: huffman
	@./huffman

test: $(OBJECTS) $(TESTS)
	@bash ./tests/run.sh

huffman: $(OBJECTS)
	$(CC) $^ -o $@

build/%.o: src/%.c src/*.h build/
	$(CC) $(CFLAGS) -c -I src/ $< -o $@

build/test_%: tests/%.c src/*.c src/*.h build/
	$(CC) $(CFLAGS) -I src/ $< $(OBJECTS) -o $@

build/:
	mkdir $@

clean : 
	rm -rf build/
	rm -rf *.dSYM
	rm -f tests/test.log

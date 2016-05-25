#include <assert.h>
#include <stdlib.h>

#include "huffman.h"

int main(void) {
    int weights[] = {8, 3, 1, 1, 1, 1, 1, 1};
    char* syms = "abcdefgh";

    huffman code;
    huffman_init(&code, syms, weights);
    huffman_encode(&code, "abcdefgh");
}

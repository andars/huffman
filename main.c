#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "huffman.h"

int main(void) {
    char buf[1024];
    char syms[256];
    int weights[256];
    int count = 256;

    for (int c = 0; c<count; c++) {
        syms[c] = c;
        weights[c] = 0;
    }

    int nread = fread(buf, sizeof(char), 1024, stdin);

    for (int i = 0; i<nread; i++) {
        int sym = buf[i];
        weights[sym]++;
    }

    huffman code;
    if (!huffman_init(&code, syms, weights, count)) return 0;
    huffman_encode(&code, buf, nread);
}

#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#define MAX_SYMBOLS 256

typedef struct tree {
    struct tree *left;
    struct tree *right;
    char symbol;
    int weight;
} tree;

typedef struct huffman {
    tree* t;
    int code[MAX_SYMBOLS];
    int code_len[MAX_SYMBOLS];
} huffman;

void huffman_init(huffman* h, char* alphabet, int freq[], int count);
void huffman_encode(huffman* h, const char* message, int n);

#endif

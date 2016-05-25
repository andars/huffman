#include <stdio.h>

#include "huffman.h"
#include "vector.h"

static int is_leaf(tree *node) {
    return !(node->left || node->right);
}

// dump vector of nodes on stdout for debug
#ifdef DEBUG
static void dump_vector(vector* v) {
    for (int i = 0; i<v->len; i++) {
        tree* l = vector_get(v, i);
        printf("sym: %c, freq: %d\n", l->symbol, l->weight);
    }
}
#endif

// insert a node into a vector used as an ordered set
//  ordered by weight 
static void set_insert(vector* v, tree* l) {
    int i = 0;
#ifdef DEBUG
    printf("inserting %c\n", l->symbol);
#endif

    if (v->len > 0) {
        tree* n = vector_get(v, 0);

        while (n->weight < l->weight) {
            i++;
            if (i >= v->len) break;
            n = vector_get(v, i);
        }

    }

#ifdef DEBUG
    printf("sym: %c, weight: %d, len: %d, i: %d\n", l->symbol,
            l->weight, v->len, i);
#endif

    vector_insert(v, l, i);
}

tree* make_leaf(char sym, int freq) {
    tree* leaf = malloc(sizeof(tree));
    leaf->right = NULL;
    leaf->left = NULL;
    leaf->symbol = sym;
    leaf->weight = freq;
    return leaf;
}

tree* huffman_generate(char* alphabet, int freq[], int count) {
    vector* v = vector_create();
    for (int i = 0; i<count; i++) {
        int f = freq[i];
        if (f > 0) {
            set_insert(v, make_leaf(alphabet[i], freq[i])); 
        }
    } 

    while (v->len > 1) {
        //extract two trees with minimum weight
        tree* t1 = vector_remove(v, 0);
        tree* t2 = vector_remove(v, 0); 

        tree* node = malloc(sizeof(tree));
        node->left = t1;
        node->right = t2;
        node->symbol = t1->symbol;
        node->weight = t1->weight + t2->weight;
    
        set_insert(v, node);
#ifdef DEBUG
        dump_vector(v);
#endif
    }

    tree* final = vector_get(v, 0);
    vector_destroy(v);
    return final;
}

static void print_encoding(huffman* h, unsigned char c) {
    int depth = h->code_len[c];
    int enc = h->code[c];
    for (int i = depth-1; i>=0; i--) {
        printf("%u", (unsigned) (enc >> i) & 1); 
    }
    printf("\n");
}

void huffman_encoding(huffman* h, tree* t, int enc, int depth) {
    if (is_leaf(t)) {
        h->code[(unsigned) t->symbol] = enc;
        h->code_len[(unsigned) t->symbol] = depth;
    } else {
        huffman_encoding(h, t->left, enc << 1, depth+1);
        huffman_encoding(h, t->right, (enc << 1) | 1, depth+1);
    }
}


void huffman_encode(huffman* h, const char* message, int n) {
    char c;
    printf("BEGIN MESSAGE\n");
    for (int i = 0; i<n; i++) {
        c = message[i];
        print_encoding(h, c);
    } 
    printf("END MESSAGE\n");
}

void huffman_init(huffman* h, char* alphabet, int freq[], int count) {
    h->t = huffman_generate(alphabet, freq, count);
    huffman_encoding(h, h->t, 0, 0);
}

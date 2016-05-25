#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "vector.h"

int main(void) {
    vector* v = vector_create();

    int* i1 = malloc(sizeof(int));
    *i1 = 92;
    vector_append(v, i1);
    assert(*(int*)vector_get(v, 0) == 92);
    free(i1);

    vector_remove(v, 0);

    for (int i = 0; i<100; i++) {
        int* i2 = malloc(sizeof(int));
        *i2 = i;
        vector_append(v, i2);
    }

    for (int i = 0; i<100; i++) {
        int* np = vector_get(v, i);
        assert(*np == i);
        free(np);
    }

    while (v->len > 0) {
        vector_remove(v, 0);
    }

    
    for (int i = 0; i<10; i++) {
        int* i2 = malloc(sizeof(int));
        *i2 = i;
        vector_insert(v, i2, 0);
    }

    for (int i = 0; i<10; i++) {
        int* np = vector_get(v, i);
        printf("%d: %d \n", i, *np);
    }
    printf("\n");

    for (int i = 9; i>=0; i--) {
        int* np = vector_remove(v, 0);
        assert(*np == i);
        free(np);
    }

    vector_destroy(v);
}

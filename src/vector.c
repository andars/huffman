#include <string.h>

#include "vector.h"

#define INIT_SIZE 10

vector* vector_create() {
    vector* v = malloc(sizeof(vector));
    if (!v) return NULL;

    v->data = malloc(sizeof(void*) * INIT_SIZE);
    if (!v->data) return NULL;

    v->size = INIT_SIZE;
    v->len = 0;
    return v;
}

void vector_destroy(vector* v) {
    free(v->data);
    free(v);
}

void expand(vector* v) {
    if (v->size <= v->len) {
        v->size = v->size * 2;
        v->data = realloc(v->data, v->size * sizeof(void*));
    }
}

void vector_append(vector* v, void* e) {
    expand(v);
    v->data[v->len] = e;
    v->len++;
}

void* vector_get(vector* v, int i) {
    return v->data[i];
}

void vector_insert(vector* v, void* e, int i) {
    expand(v);
    int n = v->len - i;
    memmove(&v->data[i+1], &v->data[i], n*sizeof(void*)); 
    v->data[i] = e;
    v->len++;
}

void* vector_remove(vector* v, int i) {
    void* ptr = v->data[i];
    int n = v->len - i;
    memmove(&v->data[i], &v->data[i+1], n*sizeof(void*));
    v->len--;
    return ptr;
}

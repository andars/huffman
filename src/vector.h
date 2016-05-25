#ifndef VECTOR_H_
#define VECTOR_H_

#include "stdlib.h"

typedef struct vector {
    void** data;
    int size;
    int len;
} vector;

vector* vector_create();
void vector_destroy(vector* v);
void vector_append(vector* v, void* e);
void* vector_get(vector* v, int i);
void vector_insert(vector* v, void* e, int i);
void* vector_remove(vector* v, int i);

#endif

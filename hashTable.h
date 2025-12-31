#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>

typedef struct Hashtable Hashtable;

Hashtable* hashtable_create(size_t elem_size, size_t capacity);

int hashtable_add(Hashtable *table, const char* key, const void* value);

int hashtable_remove(Hashtable *table, const char* key);

void hashtable_destroy(Hashtable *table);

int hastable_reserve(Hashtable *table, size_t size);
#endif

#ifndef _HASH

#define _HASH

#include "ll.h"

#define BUCKETS 100

typedef struct Hashtable Hashtable;

struct Hashtable {
    //int buckets = 10;
    LL *list_array[BUCKETS];
};

Hashtable *hash_create(void);

bool hash_put(Hashtable *, char *key, int val);

int *hash_get(Hashtable *, char *key);

void hash_destroy(Hashtable **);

#endif

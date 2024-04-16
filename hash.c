#include "hash.h"

#include "badhash.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Hashtable *hash_create(void) {
    Hashtable *table = (Hashtable *) malloc(sizeof(Hashtable));
    if (table == NULL) {
        return NULL;
    }
    for (int i = 0; i < BUCKETS; ++i) {
        (table->list_array)[i] = list_create();
    }
    return table;
}

bool hash_put(Hashtable *table, char *key, int val) {

    if (table == NULL) {
        return NULL;
    }

    unsigned int index = (unsigned int) (hash(key)) % (BUCKETS);

    item i;

    strncpy(i.key, key, sizeof(i.key) - 1);
    i.key[sizeof(i.key) - 1] = '\0';

    i.id = val;

    item *ret = list_find((table->list_array)[index], cmp, &i);

    if (ret == NULL) {
        list_add((table->list_array)[index], &i);
        return true;
    }
    return false;
}

int *hash_get(Hashtable *table, char *key) {

    if (table == NULL) {
        return NULL;
    }

    unsigned int index = hash(key) % (BUCKETS);

    item temp;
    strncpy(temp.key, key, sizeof(temp.key) - 1);
    temp.key[sizeof(temp.key) - 1] = '\0';
    item *found = list_find((table->list_array)[index], cmp, &temp);

    if (found != NULL) {
        return &(found->id);
    }
    return NULL;
}

void hash_destroy(Hashtable **table) {

    if (table == NULL || *table == NULL) {
        return;
    }
    for (int i = 0; i < BUCKETS; ++i) {
        list_destroy(&(((*table)->list_array)[i]));
    }
    free(*table);
    *table = NULL;
}

#include "badhash.h"
#include "dictwords.h"
#include "hash.h"
#include "item.h"
#include "ll.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    FILE *file;
    bool stdin_active = false;

    if (argc == 1) {
        stdin_active = true;
    } else if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    if (stdin_active == false) {
        file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("Error opening file");
            return 1;
        }
    }

    Hashtable *table = hash_create();

    int uniq_ctr = 0;
    int line_num = 1;

    char *buffer = NULL;
    size_t len = 0;
    ssize_t read;

    if (stdin_active == false) {
        read = getline(&buffer, &len, file);
    } else {
        read = getline(&buffer, &len, stdin);
    }

    while (read != -1) {

        bool uniq = hash_put(table, buffer, line_num);

        if (uniq) {
            ++uniq_ctr;
        }

        if (stdin_active == false) {
            read = getline(&buffer, &len, file);
        } else {
            read = getline(&buffer, &len, stdin);
        }
        ++line_num;
    }
    printf("%d\n", uniq_ctr);

    hash_destroy(&table);

    if (stdin_active == false) {
        fclose(file);
    }
    return 0;
}

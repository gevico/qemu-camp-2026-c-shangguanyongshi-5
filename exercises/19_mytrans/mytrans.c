// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
    char *start = str;
    size_t len;

    if (str == NULL || *str == '\0')
        return;
    while (*start && isspace((unsigned char)*start))
        start++;
    if (start != str)
        memmove(str, start, strlen(start) + 1);
    len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1]))
        len--;
    str[len] = '\0';
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
    FILE *file = fopen(filename, "r");
    char line[16384];
    char key_buf[512];

    if (!file) {
        perror("无法打开词典文件");
        return -1;
    }

    *dict_count = 0;
    while (fgets(line, (int)sizeof(line), file) != NULL) {
        char *trans_line = line;

        trim(trans_line);
        if (trans_line[0] != '#')
            continue;

        if (strlen(trans_line + 1) >= sizeof(key_buf))
            continue;
        strncpy(key_buf, trans_line + 1, sizeof(key_buf) - 1);
        key_buf[sizeof(key_buf) - 1] = '\0';
        trim(key_buf);
        if (key_buf[0] == '\0')
            continue;

        if (fgets(line, (int)sizeof(line), file) == NULL)
            break;

        trim(line);
        if (strncmp(line, "Trans:", 6) != 0)
            continue;

        if (hash_table_insert(table, key_buf, line + 6))
            (*dict_count)++;
    }

    fclose(file);
    return 0;
}

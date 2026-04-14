#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    const char *s;
    const char *slash1;
    const char *slash2;
    size_t oldlen;
    size_t newlen;

    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }
    s = cmd + 2;
    slash1 = strchr(s, '/');
    if (slash1 == NULL) {
        return -1;
    }
    slash2 = strchr(slash1 + 1, '/');
    if (slash2 == NULL) {
        return -1;
    }
    oldlen = (size_t)(slash1 - s);
    newlen = (size_t)(slash2 - (slash1 + 1));

    *old_str = malloc(oldlen + 1);
    *new_str = malloc(newlen + 1);
    if (*old_str == NULL || *new_str == NULL) {
        free(*old_str);
        free(*new_str);
        *old_str = NULL;
        *new_str = NULL;
        return -1;
    }
    memcpy(*old_str, s, oldlen);
    (*old_str)[oldlen] = '\0';
    memcpy(*new_str, slash1 + 1, newlen);
    (*new_str)[newlen] = '\0';

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    char *p = strstr(str, old);
    size_t oldlen;
    size_t newlen;
    size_t tail;

    if (p == NULL) {
        return;
    }
    oldlen = strlen(old);
    newlen = strlen(new);
    tail = strlen(p + oldlen);
    memmove(p + newlen, p + oldlen, tail + 1);
    memcpy(p, new, newlen);
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}

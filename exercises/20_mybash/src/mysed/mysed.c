#include "mysed.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    const char *s;
    const char *slash1;
    const char *slash2;
    size_t oldlen;
    size_t newlen;

    if (!cmd || !old_str || !new_str) {
        return -1;
    }

    // 初始化输出参数
    *old_str = NULL;
    *new_str = NULL;

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
    char *p;
    size_t oldlen;
    size_t newlen;
    size_t tail;

    if (!str || !old || !new) {
        return;
    }

    p = strstr(str, old);
    if (p == NULL) {
        return;
    }

    oldlen = strlen(old);
    newlen = strlen(new);
    tail = strlen(p + oldlen);

    memmove(p + newlen, p + oldlen, tail + 1);
    memcpy(p, new, newlen);
}

int __cmd_mysed(const char* rules, const char* str) {
    // 检查输入参数有效性
    if (!rules || !str) {
        fprintf(stderr, "Error: NULL rules or str parameter\n");
        return 1;
    }

    printf("rules: %s\n", rules);
    printf("str: %s\n", str);

    char* old_str = NULL;
    char* new_str = NULL;

    // 解析规则，例如 "s/old/new/"
    if (parse_replace_command(rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    if (!old_str || !new_str) {
        fprintf(stderr, "Error: Failed to parse old/new strings from rules\n");
        free(old_str);
        free(new_str);
        return 1;
    }

    // 复制原始字符串，因为我们可能会修改它（避免修改输入参数）
    char line[1024];
    strncpy(line, str, sizeof(line) - 1);
    line[sizeof(line) - 1] = '\0';  // 确保终止

    // 执行替换：在 line 中把 old_str 替换为 new_str（第一次出现）
    replace_first_occurrence(line, old_str, new_str);

    // 输出结果（建议加上换行，除非 str 本身带了）
    printf("%s\n", line);

    // 释放动态分配的内存
    free(old_str);
    free(new_str);

    return 0;
}

#include "myhash.h"
#include <ctype.h>
#include <inttypes.h>
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
    file = fopen("src/mytrans/dict.txt", "r");
  }
  if (!file) {
    file = fopen("dict.txt", "r");
  }
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

void to_lowercase(char *str) {
  for (; *str; ++str)
    *str = tolower((unsigned char)*str);
}

int __cmd_mytrans(const char* filename) {
  HashTable *table = create_hash_table();
  if (!table) {
    fprintf(stderr, "无法创建哈希表\n");
    return 1;
  }

  printf("=== 哈希表版英语翻译器（支持百万级数据）===\n");
  uint64_t dict_count = 0;
  if (load_dictionary("../exercises/20_mybash/src/mytrans/dict.txt", table, &dict_count) != 0) {
    fprintf(stderr, "加载词典失败，请确保 dict.txt 存在。\n");
    free_hash_table(table);
    return 1;
  }
  printf("词典加载完成，共计%ld词条。\n", dict_count);

  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "无法打开文件 dict.txt。\n");
    free_hash_table(table);
    return 1;
  }

  char line[256];
  while (fgets(line, sizeof(line), file) != NULL) {
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
        continue;
    }

    // 使用 strtok 按空格分割单词
    char *word = strtok(line, " ");
    while (word != NULL) {
      const char *translation = hash_table_lookup(table, word);
      printf("原文: %s\t", word);
      if (translation) {
          printf("翻译: %s\n", translation);
      } else {
          printf("未找到该单词的翻译。\n");
      }

      word = strtok(NULL, " ");
    }
  }

  free_hash_table(table);
  return 0;
}
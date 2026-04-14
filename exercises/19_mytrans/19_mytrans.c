// main.c
#include "myhash.h"
#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  HashTable *table = create_hash_table();
  FILE *file;
  char line[512];
  char word_buf[256];

  if (!table) {
    fprintf(stderr, "无法创建哈希表\n");
    return 1;
  }

  printf("=== 哈希表版英语翻译器（支持百万级数据）===\n");
  uint64_t dict_count = 0;
  if (load_dictionary("dict.txt", table, &dict_count) != 0) {
    fprintf(stderr, "加载词典失败，请确保 dict.txt 存在。\n");
    free_hash_table(table);
    return 1;
  }
  printf("词典加载完成，共计%" PRIu64 "词条。\n", dict_count);

  file = fopen("text.txt", "r");
  if (file == NULL) {
    fprintf(stderr, "无法打开文件 text.txt。\n");
    free_hash_table(table);
    return 1;
  }

  while (fgets(line, sizeof(line), file) != NULL) {
    char *tok;

    line[strcspn(line, "\r\n")] = '\0';
    if (strlen(line) == 0)
      continue;

    for (tok = strtok(line, " \t\n"); tok != NULL;
         tok = strtok(NULL, " \t\n")) {
      size_t i;
      size_t n = 0;

      for (i = 0; tok[i] != '\0' && n + 1 < sizeof(word_buf); i++) {
        if (isalpha((unsigned char)tok[i]))
          word_buf[n++] = (char)tolower((unsigned char)tok[i]);
      }
      word_buf[n] = '\0';
      if (n == 0)
        continue;

      const char *tr = hash_table_lookup(table, word_buf);
      if (tr != NULL)
        printf("原文: %s\t翻译: %s\n", word_buf, tr);
      else
        printf("原文: %s\t未找到该单词的翻译。\n", word_buf);
    }
  }

  fclose(file);
  free_hash_table(table);
  return 0;
}

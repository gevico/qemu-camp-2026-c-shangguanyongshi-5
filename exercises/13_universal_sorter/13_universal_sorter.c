#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*CompareFunc)(const void *, const void *);

int compareInt(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int compareFloat(const void *a, const void *b) {
    float diff = (*(float*)a - *(float*)b);
    return (diff > 0) ? 1 : ((diff < 0) ? -1 : 0);
}

int compareString(const void *a, const void *b) {
    return strcmp(*(char**)a, *(char**)b);
}

void sort(void *array, size_t n, size_t size, CompareFunc compare) {
    qsort(array, n, size, compare);
}

void processFile(const char *filename) {
    FILE *fin = fopen(filename, "r");
    if (!fin) {
        printf("错误: 无法打开文件 %s\n", filename);
        return;
    }

    int choice, n;
    if (fscanf(fin, "%d", &choice) != 1 || fscanf(fin, "%d", &n) != 1) {
        printf("错误: 文件 %s 格式不正确\n", filename);
        fclose(fin);
        return;
    }

    if (n > 20) n = 20;  // 最多支持20个元素

    printf("=== 处理数据来自: %s ===\n", filename);

    switch (choice) {
      case 1: {
        int arr[20];
        int i;
        for (i = 0; i < n; i++) {
            if (fscanf(fin, "%d", &arr[i]) != 1) {
                n = i;
                break;
            }
        }
        sort(arr, n, sizeof(int), compareInt);
        printf("排序后结果: ");
        for (i = 0; i < n; i++) {
            printf("%d%s", arr[i], (i == n - 1) ? "\n" : " ");
        }
        break;
      }
      case 2: {
        float arr[20];
        int i;
        for (i = 0; i < n; i++) {
            if (fscanf(fin, "%f", &arr[i]) != 1) {
                n = i;
                break;
            }
        }
        sort(arr, n, sizeof(float), compareFloat);
        printf("排序后结果: ");
        for (i = 0; i < n; i++) {
            printf("%.2f%s", arr[i], (i == n - 1) ? "\n" : " ");
        }
        break;
      }
      case 3: {
        char words[20][64];
        char *ptrs[20];
        int i;
        for (i = 0; i < n; i++) {
            if (fscanf(fin, "%63s", words[i]) != 1) {
                n = i;
                break;
            }
            ptrs[i] = words[i];
        }
        sort(ptrs, n, sizeof(char *), compareString);
        printf("排序后结果: ");
        for (i = 0; i < n; i++) {
            printf("%s%s", ptrs[i], (i == n - 1) ? "\n" : " ");
        }
        break;
      }
      default:
        printf("错误: 不支持的choice=%d\n", choice);
        break;
    }

    fclose(fin);
}

int main() {
    processFile("int_sort.txt");
    processFile("float_sort.txt");

    return 0;
}
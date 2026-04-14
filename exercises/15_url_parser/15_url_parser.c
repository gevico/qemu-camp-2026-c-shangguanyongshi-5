#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char *url)
{
    size_t len = strlen(url);
    char *buf = malloc(len + 1);
    if (buf == NULL) {
        return 1;
    }
    memcpy(buf, url, len + 1);

    char *query = strchr(buf, '?');
    if (query == NULL) {
        free(buf);
        return 1;
    }
    query++;

    while (*query != '\0') {
        char *equals;
        char *amp;

        if (*query == '&') {
            query++;
            continue;
        }

        equals = strchr(query, '=');
        if (equals == NULL) {
            free(buf);
            return 1;
        }

        *equals = '\0';
        amp = strchr(equals + 1, '&');
        if (amp != NULL) {
            *amp = '\0';
        }

        printf("key = %s, value = %s\n", query, equals + 1);

        if (amp != NULL) {
            query = amp + 1;
        } else {
            break;
        }
    }

    free(buf);
    return 0;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}

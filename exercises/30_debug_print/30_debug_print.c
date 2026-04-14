#include <stdio.h>
#if defined(DEBUG_LEVEL) && (DEBUG_LEVEL >= 2)

#define DEBUG_PRINT(fmt, ...) \
    do { \
        printf("DEBUG: func=%s, line=%d, " fmt "\n", __func__, __LINE__ + 2, ##__VA_ARGS__); \
    } while (0)

#else

#define DEBUG_PRINT(fmt, ...) do {} while (0)

#endif



























//! MUST BE ENSURE THE DEBUG_PRINT("x=%d", x) AT THE 48 LINE

// 测试代码
void test() {
    int x = 42;
    DEBUG_PRINT("x=%d", x);
}

int main() {
    test();
    return 0;
}
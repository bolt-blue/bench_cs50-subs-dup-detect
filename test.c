#include <stdio.h>

#include "detectors.c"

#define TEST(_test_func, _test_method, _test_string, _success_condition)    \
    {                                                                       \
        int res =_test_method(_test_string);                                \
        printf("%s ", res == _success_condition ? "[SUCCESS]" : "[FAIL]"); \
        printf("%s\n", #_test_func);                                       \
    }

/* Test each function in detectors.c for the following
 * - A string with no duplicates yields 0
 * - A string with duplicate at the beginning yields 1
 * - A string with duplicate at the end yields 1
 */
int main(void)
{
    printf("=== Array method ===\n");
    TEST(no_dup, array_method, "abcdefghijklmnopqrstuvwxyz", 0);
    TEST(start_dup, array_method, "aacdefghijklmnopqrstuvwxyz", 1);
    TEST(end_dup, array_method, "abcdefghijklmnopqrstuvqxyy", 1);

    printf("\n");

    printf("=== Bitflag method ===\n");
    TEST(no_dup, bitflag_method, "abcdefghijklmnopqrstuvwxyz", 0);
    TEST(start_dup, bitflag_method, "aacdefghijklmnopqrstuvwxyz", 1);
    TEST(end_dup, bitflag_method, "abcdefghijklmnopqrstuvqxyy", 1);

    return 0;
}

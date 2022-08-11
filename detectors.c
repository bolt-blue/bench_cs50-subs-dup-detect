/*
 * Each function in this file processes a single string of 26 letters to check
 * for any duplicates
 *
 * WARNING: Be careful how you include this file
 */

#include <stdint.h>

// Prototypes
int array_method(char str[26]);
int bitflag_method(char str[26]);

/*
 * Check `str` for duplicates
 *
 * Expects:
 * - `str` to only contain characters from 'a' to 'z'
 *
 * Returns:
 * 0: No duplicate found
 * 1: Duplicate found
 */
int array_method(char str[26])
{
    uint8_t check[26] = {0};

    for (int i = 0; i < 26; i++) {
        uint8_t pos = str[i] - 'a';
        if (check[pos])
            return 1;
        check[pos] = 1;
    }

    return 0;
}

/*
 * Check `str` for duplicates
 *
 * Expects:
 * - `str` to only contain characters from 'a' to 'z'
 *
 * Returns:
 * 0: No duplicate found
 * 1: Duplicate found
 */
int bitflag_method(char str[26])
{
    uint32_t check = 0;

    for (int i = 0; i < 26; i++) {
        uint32_t flag = 1 << (str[i] - 'a');
        if (check & flag)
            return 1;
        check |= flag;
    }

    return 0;
}

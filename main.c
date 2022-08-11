#include <stdint.h>
#include <stdio.h>

/*
 * Compare the speed of execution for detecting duplicate alphabetical
 * characters in a string, using:
 * a) an array
 * b) bitflags
 *
 * The strings are 26 characters long and we are testing to make sure that
 * each roman alphabetic character (a-z) only appears once
 *
 * For the purposes of this benchmark, we are assuming:
 * - that all characters are lowercase
 * - that each string only contains characters from 'a' to 'z'
 */
int main(void)
{
    uint8_t array_check[26] = {0};
    uint32_t bitflag_check = 0;

    // TODO:
    // - Test the following hardcoded files
    //   - NOTE: Refactor later to e.g. process all files in a directory
    // "random.list", "dup-second.list", "dup-final.list", "no-dup.list"

    return 0;
}

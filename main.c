#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FNAMELEN 16

// Prototypes
size_t load_list(FILE *file, size_t len, char list[len][26]);

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
 *
 * Return:
 *  0: Success
 * -1: Error
 */
int main(void)
{
    uint8_t array_check[26] = {0};
    uint32_t bitflag_check = 0;

    // TODO: Refactor later to e.g. process all files in a directory
    char list_files[][FNAMELEN] = {"random.list", "dup-second.list", "dup-final.list", "no-dup.list"};
    size_t num_files = sizeof(list_files) / sizeof(*list_files);

    for (int i = 0; i < num_files; i++) {
        FILE *f = fopen(list_files[i], "r");
        if (!f) {
            fprintf(stderr, "ERROR: Failed to open %s for processing. "
                    "Exiting\n", list_files[i]);
            return -1;
        }

        // The first line in the file should be the list length
        size_t len;
        if (fscanf(f, "%lu", &len) != 1) {
            fprintf(stderr, "ERROR: Failed to read list length from file. "
                    "Exiting\n");
            return -1;
        }

        char (*list)[26] = malloc(len * 26);

        size_t loaded = load_list(f, len, list);
        if (loaded != len)
            fprintf(stderr, "ERROR: Read %lu lines when %lu were expected\n",
                    loaded, len);

        // TODO:
        // - Time array method
        // - Time bitflag method
        // - Print results

        // Clean up
        free(list);
        fclose(f);
    }

    return 0;
}

/*
 * Read `len` lines from `file` into` list`
 *
 * Expects:
 * - Each line in the file contains a single string of 26 characters
 * - `list` is at least `len` in length
 * - `file` has at most `len` lines remaining to be read
 * TODO: Rewrite to be less blindly trusting of the input
 *
 * Returns:
 * The number of lines successfully read
 */
size_t load_list(FILE *file, size_t len, char list[len][26])
{
    size_t count = 0;
    char line[26];

    int chk = 0;
    while ((chk = fscanf(file, " %26c", line))) {
        if (chk == EOF || chk == 0)
            break;
        memcpy(list[count], line, 26);
        count++;
    }

    return count;
}

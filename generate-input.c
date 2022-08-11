#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000
#define AZLEN 26
#define SEED 0xdeadbeef

// Prototypes
int gen_random(char list[][AZLEN], size_t len);
int gen_dup_on_second(char list[][AZLEN], size_t len);
int gen_dup_on_final(char list[][AZLEN], size_t len);
int gen_no_dup(char list[][AZLEN], size_t len);
int save_list(char list[][AZLEN], size_t len, char *filename);

/*
 * Generate several alphabetical lists
 * Each list is N lines long
 * Each line contains a single string of 26 alphabetical characters 'a' to 'z'
 */
int main(void)
{
    // TODO:
    // - Error checking

    char (*list)[AZLEN] = malloc(N * AZLEN);
    char *filename;

    filename = "random.list";
    gen_random(list, N);
    save_list(list, N, filename);

    filename = "dup-second.list";
    gen_dup_on_second(list, N);
    save_list(list, N, filename);

    filename = "dup-final.list";
    gen_dup_on_final(list, N);
    save_list(list, N, filename);

    filename = "no-dup.list";
    gen_no_dup(list, N);
    save_list(list, N, filename);

    free(list);

    return 0;
}

/*
 * Generate `len` strings of length `AZLEN` consisting of a random assortment
 * of letters 'a' through 'z'
 */
int gen_random(char list[][AZLEN], size_t len)
{
    srand(SEED);
    for (int line = 0; line < len; line++) {
        for (int pos = 0; pos < AZLEN; pos++) {
            list[line][pos] = rand() % AZLEN + 'a';
        }
    }
    return 0;
}

/*
 * Generate `len` strings of length `AZLEN` consisting of one repeated letter
 */
int gen_dup_on_second(char list[][AZLEN], size_t len)
{
    srand(SEED);
    for (int line = 0; line < len; line++) {
        char c = rand() % AZLEN + 'a';
        memset(list[line], c, AZLEN);
    }
    return 0;
}

/*
 * Generate `len` strings of length `AZLEN` consisting of the first 25 letters
 * of the alphabet, followed by one duplicated letter
 * NOTE: The letter 'z' will never be duplcated but this should not be an
 * issue for this use-case
 */
int gen_dup_on_final(char list[][AZLEN], size_t len)
{
    srand(SEED);
    char alphabet[AZLEN] = {"abcdefghijklmnopqrstuvwxyz"};
    for (int line = 0; line < len; line++) {
        memcpy(list[line], alphabet, AZLEN);
    }
    for (int line = 0; line < len; line++) {
        // Only use characters from 'a' to 'y'
        char c = rand() % (AZLEN - 1) + 'a';
        list[line][AZLEN - 1] = c;
    }
    return 0;
}

/*
 * Generate `len` strings of length `AZLEN` consisting of no duplicated letters
 *
 * Start by initialising every string in `list` to be the alphabet, then
 * shuffle the letter positions
 */
int gen_no_dup(char list[][AZLEN], size_t len)
{
    srand(SEED);

    char alphabet[AZLEN] = {"abcdefghijklmnopqrstuvwxyz"};
    for (int line = 0; line < len; line++) {
        memcpy(list[line], alphabet, AZLEN);
    }

    for (int line = 0; line < len; line++) {
        for (int pos = 0; pos < AZLEN; pos++) {
            int swap_pos = rand() % AZLEN;
            char tmp = list[line][swap_pos];
            list[line][swap_pos] = list[line][pos];
            list[line][pos] = tmp;
        }
    }
    return 0;
}

/*
 * Save list to file, one line per list item
 * First line shall be the number of list items that follow
 *
 * Create file `filename` if it does not exist
 * Overwrite file `filename` if it does exist
 *
 * Expects:
 * - `list` to be at least of length `len`
 * - `filename` to be nul-terminated
 */
int save_list(char list[][AZLEN], size_t len, char *filename)
{
    FILE *outfile = fopen(filename, "w");
    if (!outfile)
        return -1;

    fprintf(outfile, "%lu\n", len);

    for (int line = 0; line < len; line++) {
        fprintf(outfile, "%.*s\n", AZLEN, list[line]);
    }

    fclose(outfile);
    return 0;
}

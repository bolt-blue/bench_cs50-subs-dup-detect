#include <stdio.h>
#include <stdlib.h>

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
    // - Allocate memory
    // - Generate:
    //   - random strings
    //   - duplicate on second char
    //   - duplicate on final char
    //   - no duplicate

    char (*list)[AZLEN] = malloc(N * AZLEN);
    char *filename;

    filename = "random.list";
    gen_random(list, N);
    save_list(list, N, filename);

    filename = "dup-second.list";
    gen_dup_on_second(list, N);
    save_list(list, N, filename);

#if 0
    filename = "dup-final.list";
    gen_dup_on_final(list, N);
    save_list(list, N, filename);

    filename = "no-dup.list";
    gen_no_dup(list, N);
    save_list(list, N, filename);
#endif

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
        for (int pos = 0; pos < AZLEN; pos++) {
            list[line][pos] = c;
        }
    }
    return 0;
}

int gen_dup_on_final(char list[][AZLEN], size_t len);
int gen_no_dup(char list[][AZLEN], size_t len);

/*
 * Save list to file, one line per list item
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

    for (int line = 0; line < len; line++) {
        fprintf(outfile, "%.*s\n", AZLEN, list[line]);
    }

    return 0;
}

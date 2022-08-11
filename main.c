#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>

#define FNAMELEN 16

typedef int (*check_func)(char [26]);

// Prototypes
size_t load_list(FILE *file, size_t len, char list[len][26]);
double process(size_t len, char list[len][26], check_func cf);
int array_method(char str[26]);
int bitflag_method(char str[26]);
double calculate_runtime(const struct rusage a, const struct rusage b);

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

        double time_array = 0.0, time_bitflags = 0.0;

        time_array = process(len, list, array_method);
        time_bitflags = process(len, list, bitflag_method);

        printf("=== %s ===\n", list_files[i]);
        printf("%-15s: %fs\n", "Array method", time_array);
        printf("%-15s: %fs\n", "Bitflag method", time_bitflags);
        printf("\n");

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

double process(size_t len, char list[len][26], check_func cf) {
    struct rusage before, after;

    getrusage(RUSAGE_SELF, &before);

    for (int line = 0; line < len; line++) {
        cf(list[line]);
    }

    getrusage(RUSAGE_SELF, &after);

    return calculate_runtime(before, after);
}

// TODO: Implement
int array_method(char str[26])
{
    return 0;
}

// TODO: Implement
int bitflag_method(char str[26])
{
    return 0;
}

/*
 * Calculate the difference in seconds between `a` and `b`
 *
 * Expects:
 * Both parameters to be valid rusage structs
 *
 * Return:
 * The number of seconds between `a` and `b`
 */
double calculate_runtime(const struct rusage b, const struct rusage a)
{
    return ((((a.ru_utime.tv_sec * 1000000 + a.ru_utime.tv_usec)
            - (b.ru_utime.tv_sec * 1000000 + b.ru_utime.tv_usec))
           + ((a.ru_stime.tv_sec * 1000000 + a.ru_stime.tv_usec)
            - (b.ru_stime.tv_sec * 1000000 + b.ru_stime.tv_usec)))
           / 1000000.0);
}

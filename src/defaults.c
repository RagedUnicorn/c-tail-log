#include <string.h>
#include <stdio.h>

#include "../include/defaults.h"

struct defaults patterns[DEFAULTS_SIZE] = {
    {
        "debug", "(DEBUG)", "\x1B[35m" /* magenta */
    }, {
        "info", "(INFO)", "\x1B[36m" /* cyan */
    }, {
        "warn", "(WARN)", "\x1B[33m" /* yellow */
    }, {
        "error", "(ERROR)", "\x1B[31m" /* red */
    }, {
        "reset", "--", "\x1B[0m" /* reset */
    }
};

/**
 * iterate over defaults struct and return the pattern if it matches the passed name
 * @param {struct defaults}
 *              all patterns
 * @param {char} name
 *              name of a single pattern
 * @return {struct defaults}
 *              returns the found pattern or NULL if no match was found
 */
struct defaults *get_pattern_by_name(struct defaults *patterns, char *name) {
    int i;

    for (i = 0; i < DEFAULTS_SIZE; i++) {
        if (strcmp(patterns[i].name, name) == 0) {
            return &patterns[i];
        }
    }

    return NULL;
}

/**
 * searches for a specific pattern with the name of 'reset' and returns it
 * @param {struct defaults}
 *                  all patterns
 * @return {struct defaults}
 *                  returns the found pattern or NULL if no match was found
 */
struct defaults *get_reset_pattern(struct defaults *patterns) {
    int i;

    for (i = 0; i < DEFAULTS_SIZE; i++) {
        if (strcmp(patterns[i].name, "reset") == 0) {
            return &patterns[i];
        }
    }

    return NULL;
}

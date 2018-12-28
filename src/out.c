#include <stdio.h>
#include <stdarg.h>

#include "../include/out.h"

/**
 * print plain text to standard output
 * @param {char} buf
 *          pointer to a buffer
 */
void out_plain(char *buf) {
    fprintf(stdout, "%s", buf);
    fflush(stdout);
}

/**
 * print colored text to standard output
 * @param {char} buf
 *          pointer to a buffer
 * @param {char} color
 *          ascii color
 * @param {char} reset
 *          ascii reset pattern
 */
void out_color(char *buf, char *color, char *reset) {
    fprintf(stdout, "%s%s%s", color, buf, reset);
    fflush(stdout);
}

#include <stdio.h>

#include "../include/defaults.h"
#include "../include/out.h"
#include "../include/opt.h"
#include "../include/logger.h"

/**
 * retrieve color pattern, reset pattern and pass to colorer
 * @param {char} buf
 *              pointer to a buffer
 * @param {char} name
 *              name of a pattern
 */
void colorize(char *buf, char *name) {
    struct defaults *pattern = get_pattern_by_name(patterns, name); /* single retrieved patterns */
    struct defaults *reset = get_reset_pattern(patterns); /* reset pattern */

    if (conf.color && pattern != NULL) {
        out_color(buf, pattern->ascii_color, reset->ascii_color);
    } else {
        out_plain(buf); /* print message in plain text */
    }
}

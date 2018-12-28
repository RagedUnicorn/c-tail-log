#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "../include/messages.h"
#include "../include/matcher.h"
#include "../include/color.h"
#include "../include/defaults.h"
#include "../include/logger.h"

/**
 * match a string against the defined patterns
 * @param {char}
 *          pointer to a buffer
 */
void match(char *buf) {
    regex_t regex;
    int reti;
    int i;

    if (strlen(buf) == 0) {
        return;
    }

    /**
     * iterate over all defaults
     * ignore 'neutral' pattern
     */
    for (i = 0; i < (sizeof(patterns) / sizeof(struct defaults)); i++) {
        if (strlen(patterns[i].name) != 0 && strlen(patterns[i].expr) != 0 && strlen(patterns[i].ascii_color) != 0) {
            if (strcmp(patterns[i].name, "neutral") != 0) {
                reti = regcomp(&regex, patterns[i].expr, REG_EXTENDED | REG_ICASE | REG_NOSUB);

                if (reti == NOK) {
                    log_formatted_error("Could not compile regex: %s\n", patterns[i].expr);
                    regfree(&regex);
                    break;
                }

                reti = regexec(&regex, buf, 0, NULL, 0);

                if (reti == REG_MATCH) {
                    /* pass to colorizing */
                    colorize(buf, patterns[i].name);
                    regfree(&regex);

                    /* break on first match, will always use its first match and ignore all following */
                    break;
                } else if (reti == REG_NOMATCH) {
                    log_formatted_debug("Message did not match pattern %s", patterns[i].expr);
                } else {
                    /* ignore failed match */
                    log_formatted_debug("Regex match failed on: %s", buf);
                }
                regfree(&regex);
            }
        }
    }
}

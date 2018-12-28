#ifndef DEFAULTS_H
#define DEFAULTS_H

#define DEFAULTS_SIZE 40

struct defaults {
    char *name; /* pattern name */
    char *expr; /* a regular expression */
    char *ascii_color; /* an ascii color */
};

extern struct defaults patterns[DEFAULTS_SIZE];

struct defaults *get_pattern_by_name(struct defaults *patterns, char *name);
struct defaults *get_reset_pattern(struct defaults *patterns);

#endif

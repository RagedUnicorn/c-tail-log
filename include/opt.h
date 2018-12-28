#ifndef OPT_H
#define OPT_H

#define MAX_PATH_SIZE 256

struct config {
    char *config; /* config name */
    char *settings; /* path to a settings file */
    int debug; /* debug mode off 0/on 1 */
    int verbose; /* verbose mode off 0/on 1 */
    int quiet; /* quiet mode off 0/on 1 */
    int color; /* color mode off 0/on 1 */
    int lines; /* how many lines are displayed on startup */
};

extern struct config conf;

int get_options(int argc, char *argv[]);

#endif

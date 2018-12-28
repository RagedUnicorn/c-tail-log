#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/opt.h"
#include "../include/logger.h"
#include "../include/messages.h"
#include "../include/help.h"
#include "../include/kevent.h"

/**
 * config: default ".ctail"
 * settings: default ""
 * debug: default 0
 * verbose: default 0
 * quiet: default 0
 * color: default 0
 * lines: default 5
 */
struct config conf = {".ctail", "", 0, 0, 0, 1, 5};

/**
 * parse all commandline arguments and return the argument offset which is used to determine
 * at what position the log-path is expected
 * returns 1 if there was no commandline argument
 * @param {int} argc
 *          argument count
 * @param {char} argv
 *          array of command line arguments
 * @returns {int}
 *          returns an offset of arguments received
 */
int get_options(int argc, char *argv[]) {
    int opt = 0;
    int long_index = 0;
    int offset = 0;

    struct option long_options[] = {
        {"verbose", no_argument, NULL, 'v'},
        {"debug", no_argument, NULL, 'd'},
        {"quiet", no_argument, NULL, 'q'},
        {"help", no_argument, NULL, 'h'},
        {"color", no_argument, NULL, 'c'},
        {"lines", required_argument, NULL, 'l'},
        {"setting", required_argument, NULL, 's'},
        {NULL, 0, 0, 0} /* zero line required by get opt long */
    };

    while ((opt = getopt_long(argc, argv,"hvdqcs:l:", long_options, &long_index )) != -1) {
        offset++;

        if (optarg != NULL) {
            offset++; /* additional inkrement for each argument passed */
        }

        switch (opt) {
            case 'd':
                conf.debug = 1;
                break;
            case 'v':
                conf.verbose = 1;
                break;
            case 'q':
                conf.quiet = 1;
                break;
            case 'h':
                print_help();
                exit(OK);
            case 'c':
                conf.color = 0;
                break;
            case 's':
                conf.settings = malloc(sizeof(char) * MAX_PATH_SIZE + 1); /* + \0 */

                if (conf.settings == NULL) {
                    log_error("Out of memory error");
                    exit(OUT_OF_MEMORY_ERROR);
                }

                strcpy(conf.settings, optarg);
                break;
            case 'l':
                if (atoi(optarg) <= MAX_QUEUE) {
                    conf.lines = atoi(optarg); /* invalid numbers will result in 0 */
                } else {
                    log_formatted_error("Only a maximum of %d lines are allowed to be displayed at startup", MAX_QUEUE);
                    exit(SIZE_RESTRICT_VIOLATION);
                }

                break;
            default:
                /* do not print an error message getopt_long generates one by itself */
                print_usage();
                exit(INVALID_USE_OF_CLI_ARGUMENTS);
        }
    }

    return offset;
}

#include <stdio.h>

#include "../include/help.h"

/**
 * print commandline usage to console
 */
void print_usage() {
    printf("usage: ctail [options][file]\n");
}

/**
 * print help to console
 */
void print_help() {
    printf("NAME\n"
        "\tctail -- display the last part of a file\n"
        "\n"
        "SYNOPSIS\n"
        "\tctail [options][file]\n"
        "\n"
        "DESCRIPTION\n"
        "\tctail is a lightweight tail -f like implementation that helps you distinguish "
        "between different loglevels by using colored output\n"
        "\n"
    ); /* split to avoid exceeding maximung length of 509 (c90) */

    printf("OPTIONS\n"
        "\t-c (--color)\n"
        "\t\tdeactivates coloring of messages if set\n"
        "\t-s (--setting)\n"
        "\t\tcustom path to a settings file [not implemented]\n"
        "\t-q (--quiet)\n"
        "\t\tsuppress all logging output including errors\n"
        "\t-d (--debug)\n"
        "\t\tactivates additional debug output\n"
        "\t-v (--verbose)\n"
        "\t\tactivates additional info output\n"
        "\t-l (--lines)\n"
        "\t\tconfigures how many lines are printed on startup\n"
    );
}

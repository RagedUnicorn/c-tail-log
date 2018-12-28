#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/select.h>

#include "writer.h"

char *messages[MESSAGE_LENGTH] = {
    "[INFO]: this is an info message",
    "[DEBUG]: this is a debug message",
    "[WARN]: this is a warn message",
    "[ERROR]: this is an error message"
};

/**
 * Write random log messages to a file
 * doc arguments file path and delay(ms)
 */
int main(int argc, char *argv[]) {
    FILE *fp; /* file pointer */
    int delay;

    if (!argv[1]) {
        fprintf(stderr, "%s [file] (delay in ms)\n", argv[0]); /* print usage */
        exit(MISSING_ARGUMENT);
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printf("%s [file] (delay in ms)\n", argv[0]); /* print usage */
        exit(OK);
    }

    if (argv[2]) {
        delay = atoi(argv[2]) * 1000; /* delay in microseconds */
    } else {
        delay = 1000000; /* default 1sec */
    }

    printf("[DEBUG]: received %s as path parameter\n", argv[1]);
    printf("[DEBUG]: delay is %s\n", argv[2]);

    srand(time(NULL)); /* random initialize one time only */

    fp = open_file(argv[1]); /* open file */

    loop(fp, delay);

    return 0;
}

/**
 * loop for writing to file
 * @param {FILE} fp
 *          filepointer
 * @param {int} delay
 *          delay between writing
 */
void loop(FILE *fp, int delay) {
    const int MICRO_SECOND = 1000000;
    struct timeval tv;

    printf("[INFO]: Opened file now starting to write log messages\n");
    printf("******************************************************\n");

    for (;;) {
        char *message = get_random_message();

        printf("%s\n", message);
        write_to_file(fp, message);

        if (delay >= MICRO_SECOND) {
            tv.tv_sec = delay / 1000000;
            tv.tv_usec = 0;
        } else {
            tv.tv_sec = 0;
            tv.tv_usec = delay;
        }

        /* hack for sleep */
        select(0, NULL, NULL, NULL, &tv);
    }
}

/**
 * open the file in the passed path and return a file pointer to it
 * @param {char} path
 *              path to the file that should get opened
 * @return {FILE}
 *              returns a filepointer on success
 */
FILE *open_file(char *path) {
    FILE *fp; /* file pointer */

    fp = fopen(path, "a"); /* append mode (file must not exist) */

    if (fp == NULL) {
        fprintf(stderr, "[ERROR]: Unable to open input file %s\n", path);
        exit(FILE_ERROR);
    }

    printf("[INFO]: Successfuly opened file %s\n", path);

    return fp; /* return file pointer */
}

/**
 * write the passed message to the passed file pointer and
 * make sure to flush after each written line
 * @param {FILE} fp
 *              filepointer
 * @param {char} message
 *              message to write to the file
 */
void write_to_file (FILE *fp, char *message) {
    fprintf(fp, "%s\n", message);
    fflush(fp);
}

/**
 * takes a random message from the messages array and returns it
 * @return {char}
 *          returns a randome message taken from messages array
 */
char *get_random_message() {
    int r = rand() % 4;

    return messages[r];
}

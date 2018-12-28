#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/util.h"
#include "../include/messages.h"
#include "../include/logger.h"

/**
 * concatenate two strings together using the passed buffer and its size to check for
 * a bufferoverflow
 * @param {char} buffer
 *          buffer that will contain both strings after concatenate
 * @param {int} size
 *          size of buffer
 * @param {char} string1
 * @param {char} string2
 */
void safe_concatenate(char *buffer, int size, char *string1, char *string2) {
    if (strlen(string1) + strlen(string2) > size) {
        log_error("Catched bufferoverflow!");
        exit(BUFFER_OVERFLOW);
    } else {
        strcat(buffer, string1);
        strcat(buffer, string2);
    }
}

/**
 * shift all elements in an array to its left one
 * @param {char} queue
 *          array that should get shifted
 * param {int} size
 *          size of array
 */
void shift_array_left(char *queue[], int size) {
    int i = 0;

    for (i = 0; i < size; i++) {
        queue[i] = queue[i + 1];
    }
}

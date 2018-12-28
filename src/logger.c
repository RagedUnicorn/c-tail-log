#include <stdio.h>
#include <stdarg.h>

#include "../include/logger.h"
#include "../include/util.h"
#include "../include/opt.h"

#define ERROR_TYPE 1
#define DEBUG_TYPE 2
#define INFO_TYPE 3

/**
 * @param {char} message
 *          message to print
 */
void log_error(char *message) {
    if (!conf.quiet) {
        fprintf(stderr, "[ERROR]: %s\n", message);
    }
}

/**
 * @param {char} message
 *          message to print
 */
void log_debug(char *message) {
    if (conf.debug && !conf.quiet) {
        fprintf(stdout, "[DEBUG]: %s\n", message);
    }
}

/**
 * @param {char} message
 *          message to print
 */
void log_info(char *message) {
    if (conf.verbose && !conf.quiet) {
        fprintf(stdout, "[INFO]: %s\n", message);
    }
}

/**
 * @param {char} message
 *          message to print
 * @param {ellipsis} ...
 *          arguments in printf style
 */
void log_formatted_error(char *message, ...) {
    if (!conf.quiet) {
        va_list args;
        va_start(args, message);
        log_formatted(message, ERROR_TYPE, args);
        va_end(args);
    }
}

/**
 * @param {char} message
 *          message to print
 * @param {ellipsis} ...
 *          arguments in printf style
 */
void log_formatted_debug(char *message, ...) {
    if (conf.debug && !conf.quiet) {
        va_list args;
        va_start(args, message);
        log_formatted(message, DEBUG_TYPE, args);
        va_end(args);
    }
}

/**
 * @param {char} message
 *          message to print
 * @param {ellipsis} ...
 *          arguments in printf style
 */
void log_formatted_info(char *message, ...) {
    if (conf.verbose && !conf.quiet) {
        va_list args;
        va_start(args, message);
        log_formatted(message, INFO_TYPE, args);
        va_end(args);
    }
}

/**
 * @param {char} message
 *          message to print
 * @param {int} type
 *          type of log message
 * @param {va_list} args
 *          arguments in printf style
 */
void log_formatted(char *message, int type, va_list args) {
    char buffer[1024] = {0};

    switch(type) {
    case ERROR_TYPE:
        safe_concatenate(buffer, 1024, "[ERROR]: ", message);
        vfprintf(stderr, buffer, args);
        fprintf(stderr, "\n");
        break;
    case DEBUG_TYPE:
        safe_concatenate(buffer, 1024, "[DEBUG]: ", message);
        vfprintf(stdout, buffer, args);
        fprintf(stdout, "\n");
        break;
    case INFO_TYPE:
        safe_concatenate(buffer, 1024, "[INFO]: ", message);
        vfprintf(stdout, buffer, args);
        fprintf(stdout, "\n");
        break;
    }
}

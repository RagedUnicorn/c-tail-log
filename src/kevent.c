#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <assert.h>

#include "../include/kevent.h"
#include "../include/ctail.h"
#include "../include/messages.h"
#include "../include/util.h"
#include "../include/matcher.h"
#include "../include/logger.h"
#include "../include/opt.h"

int _kqueue;

/**
 * register kevents
 * @param {struct log} f
 *              pointer to a struct of type log
 * @paran {int} kqueue
 *              kqueue reference
 */
void register_kevents(struct log *f, int kqueue) {
    struct kevent ke;

    _kqueue = kqueue;

    EV_SET(&ke, f->fd->_file, EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0, f);

    if (kevent(_kqueue, &ke, 1, NULL, 0, NULL) == -1) {
        log_error("Kevent error");
    }

    log_info("Events successfully registered");
}

/*
 * read the new lines from the file
 * @param {struct log} f
 *              pointer to a struct of type log
 * @param {char} buf
 *              pointer to a char buffer
 * @param {int} nbytes
 *              bytes to read added through kevent
 * @return {int}
 *              returns total amount of bytes written
 */
int read_file(struct log *f, char *buf, size_t len, int nbytes) {
    ssize_t bytes_read; /* [-1, SSIZE_MAX] */
    int total_bytes_written = 0;

    do {
        bytes_read = read_line(f->fd->_file, buf, len);

        if (bytes_read == READ_ERROR) {
            log_error("Error while reading a line");
            return READ_ERROR;
        }

        match(buf);
        memset(buf, 0x00, len);
    } while (bytes_read > 0 && total_bytes_written < nbytes);

    return total_bytes_written;
}

/**
 * read data byte by byte until a newline is detected or until the buffer is full
 * @param {int} fd
 *      file descriptor
 * @param {char} buf
 *          pointer to a char buffer
 * @param {size_t} len
 *          length to read
 * @return {int}
 *          bytes read or an error (-1)
 */
int read_line(int fd, char *buf, size_t len) {
    ssize_t bytes_read; /* [-1, SSIZE_MAX] */
    int i;

    for (i = 0; i < len; i++) {
        bytes_read = read(fd, &buf[i], 1); /* read one char at a time */

        if (bytes_read == READ_ERROR || bytes_read == END_OF_FILE) {
            return bytes_read; /* return error or EOF */
        }

        /* break on new line */
        if (buf[i] == NEW_LINE) {
            break;
        }
    }

    return i;
}

/**
 * kevent loop that handles all changes that are put into the keven queue
 */
void kq_loop() {
    struct log *f;
    struct kevent ke;
    int i;
    char buf[BUFFER_SIZE]; /* 1024 */

    memset(&ke, 0x00, sizeof(ke));
    memset(buf, 0x00, sizeof(buf));

    while (1) {
        i = kevent(_kqueue, NULL, 0, &ke, 1, NULL);

        if (i == -1) {
            log_error("Uknown kevent error");
        }

        f = (struct log *)ke.udata;

        if (ke.filter == EVFILT_READ) {
            if (ke.data < 0) {
                /* file has shrunk make sure to seek to end of file */
                log_error("File has shrunk. Ignore changes and seek to end");
                lseek(f->fd->_file, 0, SEEK_END);
                continue;
            }

            i = read_file(f, buf, sizeof(buf), ke.data);
            if (i == -1) {
                log_error("Error while reading changes");
            }

            continue;
        }
    }
}

/*
 * open a file for reading - immediately exits on error
 * @param {char} *path
 *          pointer to the path
 * @return {FILE}
 *          returns a FILE pointer
 */
FILE *open_file(char *path) {
    FILE *file_pointer = fopen(path, "rw");

    if (file_pointer == NULL) {
        log_formatted_error("An error occurred opening: %s", path);
        exit(FILE_ERROR);
    }

    log_formatted_info("Successfully opened file: %s", path);

    return file_pointer;
}

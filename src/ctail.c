#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

#include "../include/ctail.h"
#include "../include/kevent.h"
#include "../include/defaults.h"
#include "../include/matcher.h"
#include "../include/messages.h"
#include "../include/logger.h"
#include "../include/opt.h"
#include "../include/help.h"
#include "../include/util.h"

int main(int argc, char *argv[]) {
    init(argc, argv);

    return OK;
}

/**
 * init
 */
void init(int argc, char *argv[]) {
    struct log log_file;
    int kq = kqueue();
    int index;

    /* save for NULL values in argv */
    if (argc < 2) {
        log_error("Missing required argument");
        print_usage(); /* print usage to user */
        exit(MISSING_ARGUMENT_ERROR);
    }

    /* parse cli args */
    index = get_options(argc, argv);

    log_file.fd = open_file(argv[index + 1]);
    log_file.path = argv[index + 1];

    print_initial(&log_file);

    if (kq == -1) {
        log_error("Kqueue error");
        exit(FATAL_KQUEUE_ERROR);
    }

    register_kevents(&log_file, kq);
    kq_loop();
}

/**
 * print initial lines base ond the default value or the values
 * passed over the -l (--lines) flag
 * @param {struct log} f
 *              pointer to a struct of type log
 */
void print_initial(struct log *f) {
    char *queue[MAX_QUEUE] = {0}; /* queue to store lines */
    int max_lines = conf.lines;
    char *line = NULL;
    int queue_pos = 0;
    int i = 0;
    ssize_t read = 0;
    size_t len = 0;

    /* no lines to display seek to end */
    if (max_lines == 0) {
        if (lseek(f->fd->_file, 0, SEEK_END) == READ_ERROR) {
            log_error("Error occured while seeking end of file");
            exit(FILE_ERROR);
        }
        return;
    }

    /* read line for line */
    while ((read = getline(&line, &len, f->fd)) != -1) {
        if (queue_pos == max_lines) {
            shift_array_left(queue, max_lines);
            queue_pos--;
        }

        queue[queue_pos] = strdup(line);
        queue_pos++;
    }

    /* match all strings from the queue against the patterns */
    for (i = 0; i < MAX_QUEUE; i++) {
        if (queue[i] != NULL) {
            match(queue[i]);
        }
    }

    if (line) {
        free(line);
    }
}

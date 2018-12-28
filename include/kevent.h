#ifndef KEVENT_H
#define KEVENT_H

#include "./type.h"

#define READ_ERROR -1
#define END_OF_FILE 0

#define NEW_LINE '\n'
#define BUFFER_SIZE 1024
#define MAX_QUEUE 64

void kq_loop(void);
void register_kevents(struct log *f, int kqueue);
int read_file(struct log *f, char *buf, size_t len, int nbytes);
int read_line(int fd, char *buf, size_t len);
FILE *open_file(char *path);

#endif

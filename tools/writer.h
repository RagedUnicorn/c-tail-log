#ifndef WRITER_H
#define WRITER_H

#define OK 0
#define FILE_ERROR 1
#define MISSING_ARGUMENT 2
#define MESSAGE_LENGTH 4

FILE *open_file(char *path);
void write_to_file (FILE *fp, char *message);
void loop(FILE *fp, int delay);
char *get_random_message();

#endif

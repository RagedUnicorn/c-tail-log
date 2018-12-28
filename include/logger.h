#ifndef LOGGER_H
#define LOGGER_H

void log_error(char *s);
void log_debug(char *s);
void log_info(char *s);
void log_formatted_error(char *message, ...);
void log_formatted_debug (char *message, ...);
void log_formatted_info (char *message, ...);
void log_formatted(char *message, int type, va_list args);

#endif

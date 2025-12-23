#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 1024

typedef struct {
    char data[MAX_LINE_LENGTH];
    size_t length;
} Line;

typedef struct {
    Line lines[MAX_LINES];
    size_t num_lines;
} Buffer;

void buffer_init(Buffer *buffer);
void buffer_insert_char(Buffer *buffer, int x, int y, char c);
void buffer_delete_char(Buffer *buffer, int x, int y);
void buffer_backspace(Buffer *buffer, int *x, int *y);
void buffer_newline(Buffer *buffer, int *x, int *y);
void buffer_render(Buffer *buffer);

#endif

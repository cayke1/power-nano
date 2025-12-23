#include "buffer.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void buffer_init(Buffer *buffer)
{
    buffer->num_lines = 1;
    buffer->lines[0].length = 0;
    buffer->lines[0].data[0] = '\0';
}

void buffer_insert_char(Buffer *buffer, int x, int y, char c)
{
    if (y >= MAX_LINES || y >= (int)buffer->num_lines)
        return;

    Line *line = &buffer->lines[y];

    if (line->length >= MAX_LINE_LENGTH - 1)
        return;

    // Shift characters to the right
    if (x < (int)line->length)
    {
        memmove(&line->data[x + 1], &line->data[x], line->length - x);
    }

    line->data[x] = c;
    line->length++;
    line->data[line->length] = '\0';
}

void buffer_delete_char(Buffer *buffer, int x, int y)
{
    if (y >= MAX_LINES || y >= (int)buffer->num_lines)
        return;

    Line *line = &buffer->lines[y];

    if (x >= (int)line->length || line->length == 0)
        return;

    // Shift characters to the left
    memmove(&line->data[x], &line->data[x + 1], line->length - x);
    line->length--;
    line->data[line->length] = '\0';
}

void buffer_backspace(Buffer *buffer, int *x, int *y)
{
    if (*x > 0)
    {
        // Delete character before cursor
        (*x)--;
        buffer_delete_char(buffer, *x, *y);
    }
    else if (*y > 0)
    {
        // Join with previous line
        Line *curr_line = &buffer->lines[*y];
        Line *prev_line = &buffer->lines[*y - 1];

        int new_x = prev_line->length;

        // Append current line to previous line if there's space
        if (prev_line->length + curr_line->length < MAX_LINE_LENGTH)
        {
            memcpy(&prev_line->data[prev_line->length],
                   curr_line->data,
                   curr_line->length);
            prev_line->length += curr_line->length;
            prev_line->data[prev_line->length] = '\0';

            // Shift lines up
            for (size_t i = *y; i < buffer->num_lines - 1; i++)
            {
                buffer->lines[i] = buffer->lines[i + 1];
            }

            buffer->num_lines--;
            (*y)--;
            *x = new_x;
        }
    }
}

void buffer_newline(Buffer *buffer, int *x, int *y)
{
    if (buffer->num_lines >= MAX_LINES)
        return;

    Line *curr_line = &buffer->lines[*y];

    // Shift lines down
    for (size_t i = buffer->num_lines; i > (size_t)(*y + 1); i--)
    {
        buffer->lines[i] = buffer->lines[i - 1];
    }

    buffer->num_lines++;

    Line *new_line = &buffer->lines[*y + 1];

    // Split the line at cursor position
    if (*x < (int)curr_line->length)
    {
        size_t chars_to_move = curr_line->length - *x;
        memcpy(new_line->data, &curr_line->data[*x], chars_to_move);
        new_line->length = chars_to_move;
        new_line->data[new_line->length] = '\0';

        curr_line->length = *x;
        curr_line->data[curr_line->length] = '\0';
    }
    else
    {
        new_line->length = 0;
        new_line->data[0] = '\0';
    }

    (*y)++;
    *x = 0;
}

void buffer_render(Buffer *buffer)
{
    // Clear screen and move cursor to top
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    // Render each line
    for (size_t i = 0; i < buffer->num_lines; i++)
    {
        write(STDOUT_FILENO, buffer->lines[i].data, buffer->lines[i].length);
        write(STDOUT_FILENO, "\r\n", 2);
    }
}

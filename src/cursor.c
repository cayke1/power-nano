#include "cursor.h"
#include "terminal.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

static int screen_rows = 24;
static int screen_cols = 80;

static void get_window_size(void)
{
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0)
    {
        screen_rows = ws.ws_row;
        screen_cols = ws.ws_col;
    }
}

void cursor_init(Cursor *cursor)
{
    cursor->x = 0;
    cursor->y = 0;
    get_window_size();
}

void cursor_move_up(Cursor *cursor)
{
    if (cursor->y > 0)
        cursor->y--;
}

void cursor_move_down(Cursor *cursor)
{
    if (cursor->y < screen_rows - 1)
        cursor->y++;
}

void cursor_move_left(Cursor *cursor)
{
    if (cursor->x > 0)
        cursor->x--;
}

void cursor_move_right(Cursor *cursor)
{
    if (cursor->x < screen_cols - 1)
        cursor->x++;
}

void cursor_update_position(Cursor *cursor)
{
    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", cursor->y + 1, cursor->x + 1);
    write(STDOUT_FILENO, buf, strlen(buf));
}

#include "terminal.h"
#include "input.h"
#include "cursor.h"

int main(void)
{
    enter_raw_mode();

    Cursor cursor;
    cursor_init(&cursor);

    int c;
    while ((c = read_key()) != 0)
    {
        clear_screen();

        if (c == CTRL_Q)
            break;

        switch (c)
        {
        case ARROW_UP:
            cursor_move_up(&cursor);
            break;
        case ARROW_DOWN:
            cursor_move_down(&cursor);
            break;
        case ARROW_LEFT:
            cursor_move_left(&cursor);
            break;
        case ARROW_RIGHT:
            cursor_move_right(&cursor);
            break;
        case CTRL_Q:
            break;
        }

        cursor_update_position(&cursor);
    }

    return 0;
}
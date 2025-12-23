#include "terminal.h"
#include "input.h"
#include "cursor.h"
#include "buffer.h"

int main(void)
{
    enter_raw_mode();

    Cursor cursor;
    cursor_init(&cursor);

    Buffer buffer;
    buffer_init(&buffer);

    int c;
    while ((c = read_key()) != 0)
    {
        if (c == CTRL_Q) {
            clear_screen();
            break;
        }

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
        case BACKSPACE:
            buffer_backspace(&buffer, &cursor.x, &cursor.y);
            break;
        case DELETE:
            buffer_delete_char(&buffer, cursor.x, cursor.y);
            break;
        case ENTER:
            buffer_newline(&buffer, &cursor.x, &cursor.y);
            break;
        default:
            // Insert printable characters
            if (c >= 32 && c < 127)
            {
                buffer_insert_char(&buffer, cursor.x, cursor.y, c);
                cursor.x++;
            }
            break;
        }

        buffer_render(&buffer);
        cursor_update_position(&cursor);
    }

    return 0;
}
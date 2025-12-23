#ifndef CURSOR_H
#define CURSOR_H

typedef struct {
    int x;
    int y;
} Cursor;

void cursor_init(Cursor *cursor);
void cursor_move_up(Cursor *cursor);
void cursor_move_down(Cursor *cursor);
void cursor_move_left(Cursor *cursor);
void cursor_move_right(Cursor *cursor);
void cursor_update_position(Cursor *cursor);

#endif

#include "input.h"
#include <unistd.h>

int read_key(void)
{
    char c;
    if (read(STDIN_FILENO, &c, 1) != 1)
        return 0;

    if (c == ESC)
    {
        char seq[3];
        if (read(STDIN_FILENO, &seq[0], 1) != 1)
            return ESC;
        if (read(STDIN_FILENO, &seq[1], 1) != 1)
            return ESC;

        if (seq[0] == '[')
        {
            switch (seq[1])
            {
                case 'A': return ARROW_UP;
                case 'B': return ARROW_DOWN;
                case 'C': return ARROW_RIGHT;
                case 'D': return ARROW_LEFT;
            }
        }

        return ESC;
    }

    return c;
}

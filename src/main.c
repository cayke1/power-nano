#include "terminal.h"
#include "input.h"

int main(void)
{
    enter_raw_mode();

    char c;
    while ((c = read_key()) != 0)
    {
        clear_screen();
        if (c == CTRL_Q)
            break;
    }

    return 0;
}
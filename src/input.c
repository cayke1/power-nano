#include "input.h"
#include <unistd.h>

char read_key(void)
{
    char c;
    if (read(STDIN_FILENO, &c, 1) == 1)
        return c;
    return 0;
}

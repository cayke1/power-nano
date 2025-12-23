#include "terminal.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

struct termios original_termios;

void disable_raw_mode(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

void clear_screen(void)
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void enter_raw_mode(void)
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, &original_termios);
    atexit(disable_raw_mode);

    raw = original_termios;
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    raw.c_oflag &= ~(OPOST);

    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    clear_screen();
}

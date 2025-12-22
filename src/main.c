#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

struct termios original_termios;

void disable_raw_mode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

void clearScreen()
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void enter_raw_mode()
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

    clearScreen();
}

int main()
{
    enter_raw_mode();
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1)
    {
        clearScreen();
        if (c == 17)
            break;
    }
    return 0;
}
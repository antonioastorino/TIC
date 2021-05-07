#include "keyboard.h"
#include <termios.h>
#include <stdio.h>
#include <unistd.h>

struct termios initial_settings;

void Keyboard_init()
{
    struct termios settings;

    if (tcgetattr(0, &settings) < 0)
    {
        return;
    }
    initial_settings = settings;

    settings.c_lflag &= ~ICANON;
    settings.c_lflag &= ~ECHO;
    settings.c_lflag &= ~ISIG;
    settings.c_cc[VMIN]  = 1;
    settings.c_cc[VTIME] = 0;

    tcsetattr(0, TCSANOW, &settings);
}

void Keyboard_listen(void (*execute)(char))
{
    while (1)
    {
        int n = getchar();
        execute(n);
        if (n == 27) /* Escape key pressed */
        {
            break;
        }
        usleep(10000);
    }
}

void Keyboard_reset() { tcsetattr(0, TCSANOW, &initial_settings); }

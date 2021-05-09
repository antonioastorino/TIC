#include "keyboard.h"
#include <stdio.h>
#include <termios.h>
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
    settings.c_lflag &= ~ECHO; // Don't print what I type
    settings.c_lflag &= ~ISIG;
    settings.c_cc[VMIN]  = 1;
    settings.c_cc[VTIME] = 0;

    tcsetattr(0, TCSANOW, &settings);
}

void Keyboard_press(char c)
{
    pthread_mutex_lock(&keyboard_lock);
    switch (c)
    {
    case 'a':
        key_pressed.key_a = true;
        break;
    case 'd':
        key_pressed.key_d = true;
        break;
    case 's':
        key_pressed.key_s = true;
        break;
    case ' ':
        key_pressed.key_space = true;
        break;
    case 'j':
        key_pressed.key_j = true;
        break;
    case 'l':
        key_pressed.key_l = true;
        break;
    case 27:
        key_pressed.key_esc = true;
        break;
    default:
        break;
    }
    pthread_mutex_unlock(&keyboard_lock);
}

void Keyboard_listen()
{
    Keyboard_release_all();
    while (1)
    {
        int c = getchar();
        Keyboard_press(c);
        if (c == 27)
        {
            break;
        }
    }
}

void Keyboard_release_all()
{
    pthread_mutex_lock(&keyboard_lock);
    key_pressed.key_a     = false;
    key_pressed.key_d     = false;
    key_pressed.key_s     = false;
    key_pressed.key_j     = false;
    key_pressed.key_l     = false;
    key_pressed.key_space = false;
    key_pressed.key_esc   = false;
    pthread_mutex_unlock(&keyboard_lock);
}

void Keyboard_reset() { tcsetattr(0, TCSANOW, &initial_settings); }

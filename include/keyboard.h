#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <pthread.h>
#include <stdbool.h>

pthread_mutex_t keyboard_lock;

typedef struct
{
    bool key_a;
    bool key_d;
    bool key_s;
    bool key_space;
    bool key_j;
    bool key_l;
    bool key_esc;
} KeyPressed;

KeyPressed key_pressed;

void Keyboard_init();
void Keyboard_listen();
void Keyboard_reset();
void Keyboard_release_all();

#endif
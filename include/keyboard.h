#ifndef KEYBOARD_H
#define KEYBOARD_H

void Keyboard_init();
void Keyboard_listen(void (*execute)(char));
void Keyboard_reset();

#endif
#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdlib.h>
#define ROWS 20
#define COLS 10
char get_char_at(char*, int8_t, int8_t);
void print_to_buffer_at(char, int8_t, int8_t, char*);
#endif /* DISPLAY_H */
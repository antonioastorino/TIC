#ifndef DISPLAY_H
#define DISPLAY_H
#include "class_playground.h"
#include "class_tetromino.h"
#include <stdbool.h>
#include <stdlib.h>

#ifdef __linux__
typedef unsigned long long uint64_t;
typedef u_int16_t uint16_t;
#endif

void Display_print_playground(Playground*);
bool Display_update_playground(Playground*, Tetromino*);
void Display_print_header(Tetromino*, uint64_t, uint16_t);
void Display_color_playground_row(Playground*, uint8_t);
#endif /* DISPLAY_H */

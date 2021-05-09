#ifndef DISPLAY_H
#define DISPLAY_H
#include "class_arena.h"
#include "class_tetromino.h"
#include <stdbool.h>
#include <stdlib.h>

void Display_print_arena(Arena*);
bool Display_update_arena(Arena*, Tetromino*);
void Display_print_header(Tetromino*, uint8_t);
void Display_color_arena_row(Arena*, uint8_t);
#endif /* DISPLAY_H */
#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdlib.h>
#include "class_arena.h"
#include "class_block.h"
#include <stdbool.h>

void Display_print_arena(Arena*);
bool Display_update(Arena*, Block*, Block*, uint8_t);
#endif /* DISPLAY_H */
#ifndef CLASS_ARENA_H
#define CLASS_ARENA_H
#include "class_block.h"
#include <stdlib.h>
#define ROWS 20
#define COLS 11

typedef char Arena;
Arena arena_vec[ROWS * COLS + 1];
void Arena_init(Arena*);
char Arena_get_char_at(Arena*, int8_t, int8_t);
void Arena_set_char_at(Arena*, char, int8_t, int8_t);
void Arena_add_block(Arena*, Block*, char);
int Arena_cleanup_and_get_points(Arena*);

#endif /* CLASS_ARENA_H */
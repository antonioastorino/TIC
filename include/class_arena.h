#ifndef CLASS_ARENA_H
#define CLASS_ARENA_H
#include "class_tetromino.h"
#include <stdlib.h>
#define ROWS 20
#define COLS 11

typedef char Arena;
Arena arena_vec[ROWS * COLS];
void Arena_init(Arena*);
char Arena_get_char_at(Arena*, int8_t, int8_t);
void Arena_set_char_at(Arena*, char, int8_t, int8_t);
void Arena_add_tetromino(Arena*, Tetromino*, char);
void Arena_remove_row(Arena*, uint8_t);
int Arena_cleanup_and_get_points(Arena*, uint8_t*);

#endif /* CLASS_ARENA_H */
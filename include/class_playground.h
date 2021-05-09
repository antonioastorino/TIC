#ifndef CLASS_ARENA_H
#define CLASS_ARENA_H
#include "class_tetromino.h"
#include <stdlib.h>
#define ROWS 25
#define COLS 13 // left border + 10 + right border + null char

typedef char Playground;
Playground playground_vec[ROWS * COLS];
void Playground_init(Playground*);
char Playground_get_char_at(Playground*, int8_t, int8_t);
void Playground_set_char_at(Playground*, char, int8_t, int8_t);
void Playground_add_tetromino(Playground*, Tetromino*, char);
void Playground_remove_row(Playground*, uint8_t);
int Playground_cleanup_and_get_points(Playground*, uint8_t*);

#endif /* CLASS_ARENA_H */
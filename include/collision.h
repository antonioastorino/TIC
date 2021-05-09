#ifndef COLLISION_H
#define COLLISION_H
#include "class_tetromino.h"
#include <stdbool.h>

bool is_touchdown(char*, Tetromino*);
bool is_collision(char*, Tetromino*);

#endif /* COLLISION_H */
#ifndef COLLISION_H
#define COLLISION_H
#include "block.h"
#include <stdbool.h>

bool is_touchdown(char*, Block*);
bool is_collision(char*, Block*);

#endif /* COLLISION_H */
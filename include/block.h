#ifndef BLOCK_H
#define BLOCK_H
#include <stdlib.h>

typedef struct point
{
    int8_t x;
    int8_t y;
} Point;

typedef struct block
{
    u_int8_t size;
    Point* bricks;
    Point position;
} Block;

void Block_move_down(Block*);
void Block_rotate(Block*, int8_t);
void Block_new(Block*, int8_t);
void Block_destroy(Block*);
#endif /* BLOCK_H */
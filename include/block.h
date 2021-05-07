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

void move_down(Block*);
void rotate(Block* , int8_t);
void generate_block(Block *, int8_t);

#endif /* BLOCK_H */
#ifndef BLOCK_H
#define BLOCK_H
#include <stdbool.h>
#include <stdlib.h>

typedef enum
{
    DOWN,
    UP, /* used only to revert a collision */
    LEFT,
    RIGHT,
    CW,
    CCW,
} Direction;

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
    bool can_rotate;
} Block;

void Block_move(Block*, Direction);
void Block_rotate(Block*, Direction);
void Block_new(Block*);
void Block_destroy(Block*);
#endif /* BLOCK_H */
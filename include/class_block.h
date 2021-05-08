#ifndef CLASS_BLOCK_H
#define CLASS_BLOCK_H
#include <stdbool.h>
#include <stdlib.h>

#define BLOCK_SIZE 4

typedef enum
{
    DOWN,
    UP, /* used only to revert a collision */
    LEFT,
    RIGHT,
    CW,
    CCW,
} Direction;

typedef struct
{
    int8_t x;
    int8_t y;
} Point;

typedef struct
{
    Point bricks[BLOCK_SIZE];
    Point position;
    bool can_rotate;
} Block;

void Block_move(Block*, Direction);
void Block_rotate(Block*, Direction);
void Block_new(Block*);

#endif /* CLASS_BLOCK_H */
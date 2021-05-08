#include "block.h"
#include <memory.h>

void Block_move_down(Block* block) { block->position.x += 1; }

void Block_rotate(Block* block, int8_t direction)
{
    Point tmp_bricks[block->size];
    memcpy(&tmp_bricks, block->bricks, sizeof(block));
    for (u_int8_t i = 0; i < block->size; i++)
    {
        block->bricks[i].x = direction * (tmp_bricks[i].y);
        block->bricks[i].y = -direction * (tmp_bricks[i].x);
    }
}

void Block_new(Block* block, int8_t block_type)
{
    Point* bricks;
    switch (block_type)
    {
    case 0:
    {

        bricks = (Point*)malloc(4 * sizeof(Point*));
        /* Let's draw the L:
                (-1, 0)
                (0, 0) (0, 1) (0, 2)
        */
        bricks[0].x = -1;
        bricks[0].y = 0;
        bricks[1].x = 0;
        bricks[1].y = 0;
        bricks[2].x = 0;
        bricks[2].y = 1;
        bricks[3].x = 0;
        bricks[3].y = 2;

        block->size = 4;
    }
    break;
    case 1:
    {

        bricks = (Point*)malloc(4 * sizeof(Point*));
        /* Let's draw the bar:
                (0, -1) (0, 0) (0, 1) (0, 2)
        */
        bricks[0].x = 0;
        bricks[0].y = -1;
        bricks[1].x = 0;
        bricks[1].y = 0;
        bricks[2].x = 0;
        bricks[2].y = 1;
        bricks[3].x = 0;
        bricks[3].y = 2;

        block->size = 4;
    }
    break;
    default:
        break;
    }
    block->bricks     = bricks;
    block->position.x = 4;
    block->position.y = 4;
}

void Block_destroy(Block* block) {
    free(block->bricks);
    block->bricks = NULL;
}
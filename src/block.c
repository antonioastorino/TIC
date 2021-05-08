#include "block.h"
#include "logger.h"
#include <memory.h>

void Block_move(Block* block, Direction direction)
{
    switch (direction)
    {
    case DOWN:
    {
        block->position.x += 1;
    }
    break;
    case UP:
    {
        block->position.x -= 1;
    }
    break;
    case LEFT:
    {
        block->position.y -= 1;
    }
    break;
    case RIGHT:
    {
        block->position.y += 1;
    }
    default:
        break;
    }
}

void Block_rotate(Block* block, Direction direction)
{
    if (block->can_rotate)
    {
        LOG_DEBUG("Trying to execute rotation");
        int sign;
        if (direction == CCW)
        {
            sign = -1;
        }
        else if (direction == CW)
        {
            sign = 1;
        }
        else
        {
            // Wrong rotation direction
            LOG_ERROR("Wrong parameter `direction`");
            exit(1);
        }
        Point tmp_bricks[block->size];
        memcpy(&tmp_bricks, block->bricks, sizeof(block));
        for (u_int8_t i = 0; i < block->size; i++)
        {
            block->bricks[i].x = sign * (tmp_bricks[i].y);
            block->bricks[i].y = -sign * (tmp_bricks[i].x);
        }
        LOG_DEBUG("Rotation successfully executed");
    }
}

void Block_new(Block* block)
{
    char block_type = rand() % 6;
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

        block->size       = 4;
        block->can_rotate = true;
    }
    break;
    case 1:
    {

        bricks = (Point*)malloc(4 * sizeof(Point*));
        /* Mirrored 'L':
                         (-1, 2)
            (0, 0) (0, 1) (0, 2)
        */
        bricks[0].x = -1;
        bricks[0].y = 2;
        bricks[1].x = 0;
        bricks[1].y = 0;
        bricks[2].x = 0;
        bricks[2].y = 1;
        bricks[3].x = 0;
        bricks[3].y = 2;

        block->size       = 4;
        block->can_rotate = true;
    }
    break;
    case 2:
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

        block->size       = 4;
        block->can_rotate = true;
    }
    break;
    case 3:
    {

        bricks = (Point*)malloc(4 * sizeof(Point*));
        /* 'S':
             (-1, 0)
             (0, 0) (0, 1)
                    (1, 1)
        */
        bricks[0].x = -1;
        bricks[0].y = 0;
        bricks[1].x = 0;
        bricks[1].y = 0;
        bricks[2].x = 0;
        bricks[2].y = 1;
        bricks[3].x = 1;
        bricks[3].y = 1;

        block->size       = 4;
        block->can_rotate = true;
    }
    break;
    case 4:
    {

        bricks = (Point*)malloc(4 * sizeof(Point*));
        /* Mirrored 'S':
                    (-1, 1)
             (0, 0) (0, 1)
             (1, 0)
        */
        bricks[0].x = -1;
        bricks[0].y = 1;
        bricks[1].x = 0;
        bricks[1].y = 0;
        bricks[2].x = 0;
        bricks[2].y = 1;
        bricks[3].x = 1;
        bricks[3].y = 0;

        block->size       = 4;
        block->can_rotate = true;
    }
    break;
    case 5:
    {

        bricks = (Point*)malloc(4 * sizeof(Point*));
        /* Square:
             (-1, 0) (-1, 1)
             (0, 0)   (0, 1)
        */
        bricks[0].x = -1;
        bricks[0].y = 0;
        bricks[1].x = -1;
        bricks[1].y = 1;
        bricks[2].x = 0;
        bricks[2].y = 0;
        bricks[3].x = 0;
        bricks[3].y = 1;

        block->size       = 4;
        block->can_rotate = false;
    }
    break;
    default:
        break;
    }
    block->bricks     = bricks;
    block->position.x = 4;
    block->position.y = 4;
}

void Block_destroy(Block* block)
{
    free(block->bricks);
    block->bricks = NULL;
}
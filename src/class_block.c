#include "class_block.h"
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
        Point tmp_bricks[BLOCK_SIZE];
        memcpy(&tmp_bricks, block->bricks, sizeof(block));
        for (u_int8_t i = 0; i < BLOCK_SIZE; i++)
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
    switch (block_type)
    {
    case 0:
    {
        /* 'L':
                (0, -1)
                (1, -1) (1, 0) (1, 1)
        */
        block->bricks[0].x = 0;
        block->bricks[0].y = -1;
        block->bricks[1].x = 1;
        block->bricks[1].y = -1;
        block->bricks[2].x = 1;
        block->bricks[2].y = 0;
        block->bricks[3].x = 1;
        block->bricks[3].y = 1;
        block->can_rotate  = true;
    }
    break;
    case 1:
    {
        /* Mirrored 'L':
                         (0, 1)
            (-1, 0) (1, 0) (1, 1)
        */
        block->bricks[0].x = 0;
        block->bricks[0].y = 1;
        block->bricks[1].x = -1;
        block->bricks[1].y = 0;
        block->bricks[2].x = 1;
        block->bricks[2].y = 0;
        block->bricks[3].x = 1;
        block->bricks[3].y = 1;
        block->can_rotate  = true;
    }
    break;
    case 2:
    {
        /* Let's draw the bar:
                (0, -1) (0, 0) (0, 1) (0, 2)
        */
        block->bricks[0].x = 0;
        block->bricks[0].y = -1;
        block->bricks[1].x = 0;
        block->bricks[1].y = 0;
        block->bricks[2].x = 0;
        block->bricks[2].y = 1;
        block->bricks[3].x = 0;
        block->bricks[3].y = 2;
        block->can_rotate  = true;
    }
    break;
    case 3:
    {
        /* 'S':
             (-1, 0)
             (0, 0) (0, 1)
                    (1, 1)
        */
        block->bricks[0].x = -1;
        block->bricks[0].y = 0;
        block->bricks[1].x = 0;
        block->bricks[1].y = 0;
        block->bricks[2].x = 0;
        block->bricks[2].y = 1;
        block->bricks[3].x = 1;
        block->bricks[3].y = 1;
        block->can_rotate  = true;
    }
    break;
    case 4:
    {
        /* Mirrored 'S':
                    (-1, 1)
             (0, 0) (0, 1)
             (1, 0)
        */
        block->bricks[0].x = -1;
        block->bricks[0].y = 1;
        block->bricks[1].x = 0;
        block->bricks[1].y = 0;
        block->bricks[2].x = 0;
        block->bricks[2].y = 1;
        block->bricks[3].x = 1;
        block->bricks[3].y = 0;
        block->can_rotate  = true;
    }
    break;
    case 5:
    {
        /* Square:
             (-1, 0) (-1, 1)
             (0, 0)   (0, 1)
        */
        block->bricks[0].x = -1;
        block->bricks[0].y = 0;
        block->bricks[1].x = -1;
        block->bricks[1].y = 1;
        block->bricks[2].x = 0;
        block->bricks[2].y = 0;
        block->bricks[3].x = 0;
        block->bricks[3].y = 1;
        block->can_rotate  = false;
    }
    break;
    default:
        break;
    }
    block->position.x = 2;
    block->position.y = 4;
}
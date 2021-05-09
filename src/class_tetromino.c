#include "class_tetromino.h"
#include <memory.h>

void Tetromino_move(Tetromino* tetromino, Direction direction)
{
    switch (direction)
    {
    case DOWN:
    {
        tetromino->position.x += 1;
    }
    break;
    case UP:
    {
        tetromino->position.x -= 1;
    }
    break;
    case LEFT:
    {
        tetromino->position.y -= 1;
    }
    break;
    case RIGHT:
    {
        tetromino->position.y += 1;
    }
    default:
        break;
    }
}

void Tetromino_rotate(Tetromino* tetromino, Direction direction)
{
    if (tetromino->can_rotate)
    {
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
            exit(1);
        }
        Point tmp_bricks[BLOCK_SIZE];
        memcpy(&tmp_bricks, tetromino->bricks, sizeof(tetromino));
        for (u_int8_t i = 0; i < BLOCK_SIZE; i++)
        {
            tetromino->bricks[i].x = sign * (tmp_bricks[i].y);
            tetromino->bricks[i].y = -sign * (tmp_bricks[i].x);
        }
    }
}

Tetromino Tetromino_new()
{
    char tetromino_type = rand() % 7;
    Tetromino tetromino;
    switch (tetromino_type)
    {
    case 0:
    {
        /* 'L':
                (-1, -1) (-1, 0) (-1, 1)
                (0, -1)
        */
        tetromino.bricks[0].x = 0;
        tetromino.bricks[0].y = -1;
        tetromino.bricks[1].x = -1;
        tetromino.bricks[1].y = -1;
        tetromino.bricks[2].x = -1;
        tetromino.bricks[2].y = 0;
        tetromino.bricks[3].x = -1;
        tetromino.bricks[3].y = 1;
        tetromino.can_rotate  = true;
    }
    break;
    case 1:
    {
        /* Mirrored 'L':
            (-1, -1) (-1, 0) (-1, 1)
                             (0, 1)
        */
        tetromino.bricks[0].x = 0;
        tetromino.bricks[0].y = 1;
        tetromino.bricks[1].x = -1;
        tetromino.bricks[1].y = -1;
        tetromino.bricks[2].x = -1;
        tetromino.bricks[2].y = 0;
        tetromino.bricks[3].x = -1;
        tetromino.bricks[3].y = 1;
        tetromino.can_rotate  = true;
    }
    break;
    case 2:
    {
        /* Let's draw the bar:
                (0, -1) (0, 0) (0, 1) (0, 2)
        */
        tetromino.bricks[0].x = 0;
        tetromino.bricks[0].y = -1;
        tetromino.bricks[1].x = 0;
        tetromino.bricks[1].y = 0;
        tetromino.bricks[2].x = 0;
        tetromino.bricks[2].y = 1;
        tetromino.bricks[3].x = 0;
        tetromino.bricks[3].y = 2;
        tetromino.can_rotate  = true;
    }
    break;
    case 3:
    {
        /* 'S':
             (-1, 0)
             (0, 0) (0, 1)
                    (1, 1)
        */
        tetromino.bricks[0].x = -1;
        tetromino.bricks[0].y = 0;
        tetromino.bricks[1].x = 0;
        tetromino.bricks[1].y = 0;
        tetromino.bricks[2].x = 0;
        tetromino.bricks[2].y = 1;
        tetromino.bricks[3].x = 1;
        tetromino.bricks[3].y = 1;
        tetromino.can_rotate  = true;
    }
    break;
    case 4:
    {
        /* Mirrored 'S':
                    (-1, 1)
             (0, 0) (0, 1)
             (1, 0)
        */
        tetromino.bricks[0].x = -1;
        tetromino.bricks[0].y = 1;
        tetromino.bricks[1].x = 0;
        tetromino.bricks[1].y = 0;
        tetromino.bricks[2].x = 0;
        tetromino.bricks[2].y = 1;
        tetromino.bricks[3].x = 1;
        tetromino.bricks[3].y = 0;
        tetromino.can_rotate  = true;
    }
    break;
    case 5:
    {
        /* Square:
             (-1, 0) (-1, 1)
             (0, 0)   (0, 1)
        */
        tetromino.bricks[0].x = -1;
        tetromino.bricks[0].y = 0;
        tetromino.bricks[1].x = -1;
        tetromino.bricks[1].y = 1;
        tetromino.bricks[2].x = 0;
        tetromino.bricks[2].y = 0;
        tetromino.bricks[3].x = 0;
        tetromino.bricks[3].y = 1;
        tetromino.can_rotate  = false;
    }
    break;
    case 6:
    {
        /* 'T':
                    (-1, 0)
            (0, -1) (0, 0)  (0, 1)
        */
        tetromino.bricks[0].x = -1;
        tetromino.bricks[0].y = 0;
        tetromino.bricks[1].x = 0;
        tetromino.bricks[1].y = -1;
        tetromino.bricks[2].x = 0;
        tetromino.bricks[2].y = 0;
        tetromino.bricks[3].x = 0;
        tetromino.bricks[3].y = 1;
        tetromino.can_rotate  = true;
    }
    break;
    default:
        break;
    }
    tetromino.position.x = 1;
    tetromino.position.y = 4;
    return tetromino;
}
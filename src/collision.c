#include "collision.h"
#include "class_playground.h"
#include "display.h"

bool is_touchdown(Playground* playground_vec, Tetromino* tetromino)
{
    for (uint8_t i = 0; i < BLOCK_SIZE; i++)
    {
        if (Playground_get_char_at(playground_vec,
                                   tetromino->bricks[i].x + tetromino->position.x + 1,
                                   tetromino->bricks[i].y + tetromino->position.y)
            != ' ')
        {
            return true;
        }
    }
    return false;
}

bool is_collision(Playground* playground_vec, Tetromino* tetromino)
{
    for (uint8_t i = 0; i < BLOCK_SIZE; i++)
    {
        if (Playground_get_char_at(playground_vec, tetromino->bricks[i].x + tetromino->position.x,
                                   tetromino->bricks[i].y + tetromino->position.y)
            != ' ')
        {
            return true;
        }
    }
    return false;
}
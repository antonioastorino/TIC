#include "collision.h"
#include "class_arena.h"
#include "display.h"

bool is_touchdown(Arena* arena_vec, Tetromino* tetromino)
{
    for (uint8_t i = 0; i < BLOCK_SIZE; i++)
    {
        if (Arena_get_char_at(arena_vec, tetromino->bricks[i].x + tetromino->position.x + 1,
                              tetromino->bricks[i].y + tetromino->position.y)
            != ' ')
        {
            return true;
        }
    }
    return false;
}

bool is_collision(Arena* arena_vec, Tetromino* tetromino)
{
    for (uint8_t i = 0; i < BLOCK_SIZE; i++)
    {
        if (Arena_get_char_at(arena_vec, tetromino->bricks[i].x + tetromino->position.x,
                              tetromino->bricks[i].y + tetromino->position.y)
            != ' ')
        {
            return true;
        }
    }
    return false;
}
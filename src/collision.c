#include "collision.h"
#include "class_arena.h"
#include "display.h"

bool is_touchdown(Arena* arena_vec, Block* block)
{
    for (uint8_t i = 0; i < BLOCK_SIZE; i++)
    {
        if (Arena_get_char_at(arena_vec, block->bricks[i].x + block->position.x + 1,
                              block->bricks[i].y + block->position.y)
            != ' ')
        {
            return true;
        }
    }
    return false;
}

bool is_collision(Arena* arena_vec, Block* block)
{
    for (uint8_t i = 0; i < BLOCK_SIZE; i++)
    {
        if (Arena_get_char_at(arena_vec, block->bricks[i].x + block->position.x,
                              block->bricks[i].y + block->position.y)
            != ' ')
        {
            return true;
        }
    }
    return false;
}
#include "collision.h"
#include "display.h"

bool is_touchdown(char* buffer, Block* block)
{
    for (uint8_t i = 0; i < block->size; i++)
    {
        if (get_char_at(buffer, block->bricks[i].x + block->position.x + 1,
                        block->bricks[i].y + block->position.y)
            != ' ')
        {
            return true;
        }
    }
    return false;
}

bool is_collision(char* buffer, Block* block)
{
    for (uint8_t i = 0; i < block->size; i++)
    {
        if (get_char_at(buffer, block->bricks[i].x + block->position.x,
                        block->bricks[i].y + block->position.y)
            != ' ')
        {
            return true;
        }
    }
    return false;
}
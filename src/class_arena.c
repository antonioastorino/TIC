#include "class_arena.h"
#include <memory.h>
// #include <stdio.h>

void Arena_init(Arena* arena_vec)
{
    memset(arena_vec, ' ', ROWS * COLS);
    for (int row = 0; row < ROWS - 1; row++)
    {
        // Left margin.
        arena_vec[row * COLS] = '|';
        // Right margin.
        arena_vec[row * COLS + COLS - 2] = '|';
        // EOL
        arena_vec[row * COLS + COLS - 1] = '\0';
    }
    for (int col = 0; col < COLS - 1; col++)
    {
        arena_vec[(ROWS - 1) * COLS + col] = '-';
    }
    arena_vec[ROWS * COLS - 1] = '\0';
}

char Arena_get_char_at(Arena* arena_vec, int8_t x, int8_t y) { return arena_vec[x * COLS + y]; }

void Arena_set_char_at(Arena* arena_vec, char c, int8_t x, int8_t y)
{
    if (x < ROWS && y < COLS)
    {
        arena_vec[x * COLS + y] = c;
    }
    else
    {
        exit(1);
    }
}

void Arena_add_block(Arena* arena_vec, Block* block, char symbol)
{
    for (u_int8_t i = 0; i < BLOCK_SIZE; i++)
    {
        Arena_set_char_at(arena_vec, symbol, block->bricks[i].x + block->position.x,
                          block->bricks[i].y + block->position.y);
    }
}

void Arena_remove_row(Arena* arena_vec, uint8_t start_row)
{
    for (uint8_t row = start_row; row > 0; row--)
    {
        for (uint8_t col = 1; col < COLS - 1; col++)
        {
            Arena_set_char_at(arena_vec, Arena_get_char_at(arena_vec, row - 1, col), row, col);
        }
    }
}

int Arena_cleanup_and_get_points(Arena* arena_vec, uint8_t* complete_row)
{
    int complete_row_counter = 0;
    for (uint8_t row = 3; row < ROWS -1; row++)
    {
        bool complete = true;
        for (uint8_t col = 1; col < COLS - 1; col++)
        {
            if (Arena_get_char_at(arena_vec, row, col) == ' ')
            {
                complete = false;
                continue;
            }
        }
        if (complete)
        { // Save the last completed row (with hightest index);
            *complete_row = row;
            complete_row_counter++;
        }
    }
    return complete_row_counter;
}
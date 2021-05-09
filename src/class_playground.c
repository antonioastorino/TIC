#include "class_playground.h"
#include <memory.h>
// #include <stdio.h>

void Playground_init(Playground* playground_vec)
{
    memset(playground_vec, ' ', ROWS * COLS);
    for (int row = 0; row < ROWS - 1; row++)
    {
        // Left margin.
        playground_vec[row * COLS] = '|';
        // Right margin.
        playground_vec[row * COLS + COLS - 2] = '|';
        // EOL
        playground_vec[row * COLS + COLS - 1] = '\0';
    }
    for (int col = 0; col < COLS - 1; col++)
    {
        playground_vec[(ROWS - 1) * COLS + col] = '-';
    }
    playground_vec[ROWS * COLS - 1] = '\0';
}

char Playground_get_char_at(Playground* playground_vec, int8_t x, int8_t y)
{
    return playground_vec[x * COLS + y];
}

void Playground_set_char_at(Playground* playground_vec, char c, int8_t x, int8_t y)
{
    if (x < ROWS && y < COLS)
    {
        playground_vec[x * COLS + y] = c;
    }
    else
    {
        exit(1);
    }
}

void Playground_add_tetromino(Playground* playground_vec, Tetromino* tetromino, char symbol)
{
    for (u_int8_t i = 0; i < BLOCK_SIZE; i++)
    {
        Playground_set_char_at(playground_vec, symbol,
                               tetromino->bricks[i].x + tetromino->position.x,
                               tetromino->bricks[i].y + tetromino->position.y);
    }
}

void Playground_remove_row(Playground* playground_vec, uint8_t complete_row)
{
    for (uint8_t row = complete_row; row > 0; row--)
    {
        for (uint8_t col = 1; col < COLS - 1; col++)
        {
            Playground_set_char_at(playground_vec,
                                   Playground_get_char_at(playground_vec, row - 1, col), row, col);
        }
    }
}

int Playground_cleanup_and_get_points(Playground* playground_vec, uint8_t* complete_row_vec)
{
    int complete_row_counter = 0;
    for (uint8_t row = 3; row < ROWS - 1; row++)
    {
        bool complete = true;
        for (uint8_t col = 1; col < COLS - 1; col++)
        {
            if (Playground_get_char_at(playground_vec, row, col) == ' ')
            {
                complete = false;
                continue;
            }
        }
        if (complete)
        { // Save the row number of the current row;
            complete_row_vec[complete_row_counter] = row;
            complete_row_counter++;
        }
    }
    return complete_row_counter;
}
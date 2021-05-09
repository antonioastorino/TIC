#include "display.h"
#include "collision.h"
#include "keyboard.h"
#include <memory.h>
#include <stdio.h>
#include <unistd.h>
#define PREVIEW_ROWS 3
#define PREVIEW_COLS 4

void Display_print_arena(Arena* arena_vec)
{
    printf("\e[1m");
    for (int i = 0; i < ROWS; i++)
    {
        printf("    %s\n", &arena_vec[i * COLS]);
    }
    printf("\e[0m\e[%dA\e[0E", ROWS + 1);
}

void Display_print_header(Tetromino* next_tetromino, uint8_t score)
{
    char preview_buf[PREVIEW_ROWS][PREVIEW_COLS];
    printf("\e[4A\e[7C");
    memset(&preview_buf, ' ', sizeof(preview_buf));
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        preview_buf[next_tetromino->bricks[i].x + 1][next_tetromino->bricks[i].y + 1] = 'X';
    }
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            printf("%c", preview_buf[row][col]);
        }
        printf("\n\e[7C");
    }
    printf("\e[3F NEXT:\e[3E");
    printf(" SCORE: %u\n", score);
}

bool Display_update_arena(Arena* buffer, Tetromino* curr_tetromino)
{
    pthread_mutex_lock(&keyboard_lock);
    if (key_pressed.key_esc)
    {
        return false;
    }
    if (key_pressed.key_a)
    {
        Tetromino_move(curr_tetromino, LEFT);
        if (is_collision(buffer, curr_tetromino))
        {
            Tetromino_move(curr_tetromino, RIGHT);
        }
    }
    else if (key_pressed.key_d)
    {
        Tetromino_move(curr_tetromino, RIGHT);
        if (is_collision(buffer, curr_tetromino))
        {
            Tetromino_move(curr_tetromino, LEFT);
        }
    }
    if (key_pressed.key_s)
    {
        Tetromino_move(curr_tetromino, DOWN);
        if (is_collision(buffer, curr_tetromino))
        {
            Tetromino_move(curr_tetromino, UP);
        }
    }
    if (key_pressed.key_space)
    {
        while (!is_touchdown(buffer, curr_tetromino))
        {
            Tetromino_move(curr_tetromino, DOWN);
            usleep(5000);
            Arena_add_tetromino(buffer, curr_tetromino, '#');
            Display_print_arena(buffer);
            // Remove tetromino from the buffer after printing it.
            Arena_add_tetromino(buffer, curr_tetromino, ' ');
        }
    }
    if (key_pressed.key_j)
    {
        Tetromino_rotate(curr_tetromino, CCW);
        if (is_collision(buffer, curr_tetromino))
        {
            Tetromino_rotate(curr_tetromino, CW);
        }
    }
    if (key_pressed.key_l)
    {
        Tetromino_rotate(curr_tetromino, CW);
        if (is_collision(buffer, curr_tetromino))
        {
            Tetromino_rotate(curr_tetromino, CCW);
        }
    }
    pthread_mutex_unlock(&keyboard_lock);
    Keyboard_release_all();
    Arena_add_tetromino(buffer, curr_tetromino, '#');
    Display_print_arena(buffer);
    // Remove tetromino from the buffer after printing it to avoid self collisions.
    Arena_add_tetromino(buffer, curr_tetromino, ' ');
    return true;
}

void Display_color_arena_row(Arena* arena_vec, uint8_t row)
{
    // Move from the arena top to `row`.
    printf("\e[1m\e[%dE\e[34m", row);
    // Print the row.
    printf("    %s\n", &arena_vec[row * COLS]);
    // Go back to the arena top.
    printf("\e[0m\e[%dA", row + 1);
    usleep(50000);
}
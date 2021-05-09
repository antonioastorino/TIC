#include "display.h"
#include "collision.h"
#include "keyboard.h"
#include <memory.h>
#include <stdio.h>
#include <unistd.h>
#define PREVIEW_ROWS 3
#define PREVIEW_COLS 4

void Display_print_playground(Playground* playground_vec)
{
    printf("\e[1m");
    for (int i = 0; i < ROWS; i++)
    {
        printf("    %s\n", &playground_vec[i * COLS]);
    }
    printf("\e[0m\e[%dA\e[0E", ROWS + 1);
}

void Display_print_header(Tetromino* next_tetromino, uint64_t score, uint16_t curr_level)
{
    printf("\e[7F"); // Go to the top of the header
    printf("  \e[K\e[32m LEVEL: %hu\n", (uint16_t)(curr_level + 1));
    printf("  \e[K SCORE: %llu\e[0m\n\n", score);
    char preview_buf[PREVIEW_ROWS][PREVIEW_COLS];
    printf("\e[10C");
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
        printf("\n\e[10C");
    }
    // Go up and print "NEXT", then go down again.
    printf("\e[3F NEXT:\e[3E\n");
}

bool Display_update_playground(Playground* buffer, Tetromino* curr_tetromino)
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
            Playground_add_tetromino(buffer, curr_tetromino, '#');
            Display_print_playground(buffer);
            // Remove tetromino from the buffer after printing it.
            Playground_add_tetromino(buffer, curr_tetromino, ' ');
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
    Playground_add_tetromino(buffer, curr_tetromino, '#');
    Display_print_playground(buffer);
    // Remove tetromino from the buffer after printing it to avoid self collisions.
    Playground_add_tetromino(buffer, curr_tetromino, ' ');
    return true;
}

void Display_color_playground_row(Playground* playground_vec, uint8_t row)
{
    // Move from the playground top to `row`.
    printf("\e[1m\e[%dE\e[34m", row);
    // Print the row.
    printf("    %s\n", &playground_vec[row * COLS]);
    // Go back to the playground top.
    printf("\e[0m\e[%dA", row + 1);
    usleep(80000);
}
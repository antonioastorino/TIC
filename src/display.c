#include "display.h"
#include "collision.h"
#include "keyboard.h"
#include "logger.h"
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

void Display_print_header(Block* next_block, uint8_t score)
{
    char preview_buf[PREVIEW_ROWS][PREVIEW_COLS];
    printf("\e[4A\e[7C");
    memset(&preview_buf, ' ', sizeof(preview_buf));
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        preview_buf[next_block->bricks[i].x + 1][next_block->bricks[i].y + 1] = 'X';
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

bool Display_update_arena(Arena* buffer, Block* curr_block)
{
    pthread_mutex_lock(&keyboard_lock);
    if (key_pressed.key_esc)
    {
        return false;
    }
    if (key_pressed.key_a)
    {
        Block_move(curr_block, LEFT);
        if (is_collision(buffer, curr_block))
        {
            Block_move(curr_block, RIGHT);
        }
    }
    else if (key_pressed.key_d)
    {
        Block_move(curr_block, RIGHT);
        if (is_collision(buffer, curr_block))
        {
            Block_move(curr_block, LEFT);
        }
    }
    if (key_pressed.key_s)
    {
        Block_move(curr_block, DOWN);
        if (is_collision(buffer, curr_block))
        {
            Block_move(curr_block, UP);
        }
    }
    if (key_pressed.key_space)
    {
        while (!is_touchdown(buffer, curr_block))
        {
            Block_move(curr_block, DOWN);
            usleep(5000);
            Arena_add_block(buffer, curr_block, '#');
            Display_print_arena(buffer);
            // Remove block from the buffer after printing it.
            Arena_add_block(buffer, curr_block, ' ');
        }
    }
    if (key_pressed.key_j)
    {
        Block_rotate(curr_block, CCW);
        if (is_collision(buffer, curr_block))
        {
            Block_rotate(curr_block, CW);
        }
    }
    if (key_pressed.key_l)
    {
        Block_rotate(curr_block, CW);
        if (is_collision(buffer, curr_block))
        {
            Block_rotate(curr_block, CCW);
        }
    }
    pthread_mutex_unlock(&keyboard_lock);
    Keyboard_release_all();
    Arena_add_block(buffer, curr_block, '#');
    Display_print_arena(buffer);
    // Remove block from the buffer after printing it.
    Arena_add_block(buffer, curr_block, ' ');
    return true;
}
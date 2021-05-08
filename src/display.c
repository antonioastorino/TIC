#include "display.h"
#include "collision.h"
#include "keyboard.h"
#include "logger.h"
#include <stdio.h>
#include <unistd.h>

void Display_print_arena(Arena* arena_vec) { fprintf(stdout, "%s\e[%dA\e[0E", arena_vec, ROWS); }

bool Display_update(Arena* buffer, Block* curr_block, Block* next_block, uint8_t score)
{

    char preview_buf[3][4];
    printf("\e[4A");
    memset(&preview_buf, ' ', sizeof(preview_buf));
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        preview_buf[next_block->bricks[i].x + 1][next_block->bricks[i].y + 1] = 'Y';
    }
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            printf("%c", preview_buf[row][col]);
        }
        printf("\n");
    }

    printf("SCORE: %u\n", score);
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
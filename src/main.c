#include "class_block.h"
#include "collision.h"
#include "common.h"
#include "display.h"
#include "keyboard.h"
#include "logger.h"
#include <memory.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char buffer[ROWS * COLS + 1];
bool g_run = true;
Block curr_block;

void print_block_to_buffer(Block* block, char* buffer, char symbol)
{
    for (u_int8_t i = 0; i < BLOCK_SIZE; i++)
    {
        print_to_buffer_at(symbol, block->bricks[i].x + block->position.x,
                           block->bricks[i].y + block->position.y, buffer);
    }
}

void print_buffer(char* buffer) { fprintf(stdout, "%s\e[%dA\e[0E", buffer, ROWS); }

void buffer_remove_row(char* buffer, u_int8_t start_row)
{
    for (uint8_t row = start_row; row > 2; row--)
    {
        for (uint8_t col = 1; col < COLS - 1; col++)
        {
            print_to_buffer_at(get_char_at(buffer, row - 1, col), row, col, buffer);
        }
    }
}

void buffer_cleanup(char* buffer)
{

    for (uint8_t row = ROWS - 2; row > 2; row--)
    {
        bool complete = true;
        for (uint8_t col = 1; col < COLS - 1; col++)
        {
            if (get_char_at(buffer, row, col) == ' ')
            {
                complete = false;
                continue;
            }
        }
        if (complete)
        {
            buffer_remove_row(buffer, row);
            row++;
        }
    }
}

void scene_update(char* buffer, uint8_t score)
{
    printf("\e[1ASCORE: %u\n", score);
    pthread_mutex_lock(&keyboard_lock);
    if (key_pressed.key_esc)
    {
        g_run = false;
        return;
    }
    if (key_pressed.key_a)
    {
        Block_move(&curr_block, LEFT);
        if (is_collision(buffer, &curr_block))
        {
            Block_move(&curr_block, RIGHT);
        }
    }
    else if (key_pressed.key_d)
    {
        Block_move(&curr_block, RIGHT);
        if (is_collision(buffer, &curr_block))
        {
            Block_move(&curr_block, LEFT);
        }
    }
    if (key_pressed.key_s)
    {
        Block_move(&curr_block, DOWN);
        if (is_collision(buffer, &curr_block))
        {
            Block_move(&curr_block, UP);
        }
    }
    if (key_pressed.key_space)
    {
        while (!is_touchdown(buffer, &curr_block))
        {
            Block_move(&curr_block, DOWN);
            usleep(5000);
            print_block_to_buffer(&curr_block, buffer, '#');
            print_buffer(buffer);
            // Remove block from the buffer after printing it.
            print_block_to_buffer(&curr_block, buffer, ' ');
        }
    }
    if (key_pressed.key_j)
    {
        Block_rotate(&curr_block, CCW);
        if (is_collision(buffer, &curr_block))
        {
            Block_rotate(&curr_block, CW);
        }
    }
    if (key_pressed.key_l)
    {
        Block_rotate(&curr_block, CW);
        if (is_collision(buffer, &curr_block))
        {
            Block_rotate(&curr_block, CCW);
        }
    }
    pthread_mutex_unlock(&keyboard_lock);
    Keyboard_release_all();
    print_block_to_buffer(&curr_block, buffer, '#');
    print_buffer(buffer);
    // Remove block from the buffer after printing it.
    print_block_to_buffer(&curr_block, buffer, ' ');
}

void exit_game()
{
    Keyboard_reset();
    // Make the cursor visible again.
    printf("\e[?25h");
}

int main()
{
    // Clear screen and make cursor invisible.
    printf("\e[2J\e[?25l");
    Keyboard_init();
    init_logger("logs.log", "logs.log");
    pthread_t keyboard_t;
    void* fn = Keyboard_listen;
    pthread_create(&keyboard_t, NULL, fn, NULL);

    memset(&buffer, ' ', ROWS * COLS);
    // Set all the EOL's
    for (int row = 0; row < ROWS - 1; row++)
    {
        buffer[row * COLS]            = '\\';
        buffer[row * COLS + COLS - 2] = '/';
        buffer[row * COLS + COLS - 1] = '\n';
    }
    for (int col = 0; col < COLS - 1; col++)
    {
        buffer[(ROWS - 1) * COLS + col] = '-';
    }
    buffer[ROWS * COLS] = '\0';
    srand(time(0));
    Block_new(&curr_block);

    int frame_count = 0;
    uint8_t score   = 0;
    while (g_run)
    {
        scene_update(buffer, score);
        usleep(10000);

        // Block_rotate(&curr_block, CCW);
        if (frame_count++ >= 100)
        {
            frame_count = 0;
            if (is_touchdown(buffer, &curr_block))
            {
                print_block_to_buffer(&curr_block, buffer, '0');
                Block_new(&curr_block);
                buffer_cleanup(buffer);
                continue;
            }
            Block_move(&curr_block, DOWN);
        }
    }

    pthread_join(keyboard_t, NULL);
    exit_game();

    return 0;
}

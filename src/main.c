#include "block.h"
#include "keyboard.h"
#include <memory.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "display.h"
#include "collision.h"

#define CW 1
#define CCW -1

char buffer[ROWS * COLS + 1];
bool g_run = true;



void print_block_to_buffer(Block* block, char* buffer, char symbol)
{
    for (u_int8_t i = 0; i < block->size; i++)
    {
        print_to_buffer_at(symbol, block->bricks[i].x + block->position.x,
                           block->bricks[i].y + block->position.y, buffer);
    }
}

void print_buffer(char* buffer) { fprintf(stdout, "%s\e[%dA\e[0E", buffer, ROWS); }

void execute(char c)
{
    switch (c)
    {
    case 27 /* escape */:
        g_run = false;
        break;

    default:
        break;
    }
}

void exit_game() { Keyboard_reset(); }

int main()
{
    printf("\e[2J");
    Keyboard_init();
    pthread_t keyboard_t;
    void* fn = Keyboard_listen;
    pthread_create(&keyboard_t, NULL, fn, execute);
    Block curr_block;

    memset(&buffer, ' ', ROWS * COLS);
    // Set all the EOL
    for (int row = 0; row < ROWS - 1; row++)
    {
        buffer[row * COLS] = 48 + (row % 10);
        buffer[row * COLS + COLS - 2] = '/';
        buffer[row * COLS + COLS - 1] = '\n';
    }
    for (int col = 0; col < COLS -1; col ++) {
        buffer[(ROWS - 1) * COLS + col] = '-'; 
    }
    buffer[ROWS * COLS] = '\0';
    Block_new(&curr_block, 0);
    while (g_run)
    {
        print_block_to_buffer(&curr_block, buffer, '#');
        print_buffer(buffer);
        usleep(100000);
        print_block_to_buffer(&curr_block, buffer, ' ');
        if (is_touchdown(buffer, &curr_block))
        {
            print_block_to_buffer(&curr_block, buffer, '#');
            Block_destroy(&curr_block);
            Block_new(&curr_block, 1);
            continue;
        }
        Block_move_down(&curr_block);
        // Block_rotate(&curr_block, CCW);
    }

    pthread_join(keyboard_t, NULL);
    exit_game();

    return 0;
}

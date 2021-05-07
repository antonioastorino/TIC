#include "block.h"
#include "keyboard.h"
#include <memory.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROWS 30
#define COLS 20
#define CW 1
#define CCW -1

char buffer[ROWS * COLS + 1];
bool g_run = true;

void print_to_buffer_at(char c, int8_t x, int8_t y, char* buffer)
{
    if (x < ROWS && y < COLS)
    {
        buffer[x * COLS + y] = c;
    }
    else
    {
        exit(1);
    }
}

void print_block_to_buffer(Block* block, char* buffer, char symbol)
{
    for (u_int8_t i = 0; i < block->size; i++)
    {
        print_to_buffer_at(symbol, block->bricks[i].x + block->position.x,
                           block->bricks[i].y + block->position.y, buffer);
    }
}

void print_buffer(char* buffer) { fprintf(stdout, "%s\e[%dA", buffer, ROWS); }

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
    generate_block(&curr_block, 0);

    memset(&buffer, ' ', ROWS * COLS);
    // Set all the EOL
    for (int row = 0; row < ROWS; row++)
    {
        buffer[row * COLS + COLS - 1] = '\n';
    }
    buffer[ROWS * COLS] = '\0';

    for (int count = 0; count < 10 && g_run == true; count++)
    {
        print_block_to_buffer(&curr_block, buffer, '#');
        print_buffer(buffer);
        sleep(1);
        print_block_to_buffer(&curr_block, buffer, ' ');
        // print_buffer(buffer);
        move_down(&curr_block);
        rotate(&curr_block, CCW);
    }

    pthread_join(keyboard_t, NULL);
    exit_game();

    return 0;
}

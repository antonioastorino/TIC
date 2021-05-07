#include "keyboard.h"
#include <ctype.h>
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

typedef struct point
{
    int8_t x;
    int8_t y;
} Point;

typedef struct block
{
    u_int8_t size;
    Point* bricks;
    Point position;
} Block;

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

void move_down(Block* block) { block->position.x += 1; }

void rotate(Block* block, int8_t direction)
{
    Point tmp_bricks[block->size];
    memcpy(&tmp_bricks, block->bricks, sizeof(block));
    // for (u_int8_t i = 0; i < block->size; i++)
    // {
    // 	printf("new x = %d, old x = %d\n", tmp_bricks[i].x, block->bricks[i].x);
    // }
    for (u_int8_t i = 0; i < block->size; i++)
    {
        block->bricks[i].x = direction * (tmp_bricks[i].y);
        block->bricks[i].y = -direction * (tmp_bricks[i].x);
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

void print_buffer(char* buffer) { fprintf(stdout, "\e[2J%s", buffer); }

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
    Keyboard_init();
    pthread_t keyboard_t;
    void* fn = Keyboard_listen;
    pthread_create(&keyboard_t, NULL, fn, execute);

    Point* bricks = (Point*)malloc(4 * sizeof(Point*));
    /* Let's draw the L:
            (-1, 0)
            (0, 0) (0, 1) (0, 2)
    */
    bricks[0].x = -1;
    bricks[0].y = 0;
    bricks[1].x = 0;
    bricks[1].y = 0;
    bricks[2].x = 0;
    bricks[2].y = 1;
    bricks[3].x = 0;
    bricks[3].y = 2;

    Block curr_block = {.size     = 4,
                        .bricks   = bricks,
                        .position = {
                            .x = 4,
                            .y = 4,
                        }};

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

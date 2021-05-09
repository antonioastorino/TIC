#include "class_arena.h"
#include "class_block.h"
#include "collision.h"
#include "display.h"
#include "keyboard.h"
#include <memory.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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
    Arena_init(arena_vec);
    pthread_t keyboard_t;
    void* fn = Keyboard_listen;
    pthread_create(&keyboard_t, NULL, fn, NULL);

    srand(time(0));
    Block curr_block = Block_new();
    Block next_block = Block_new();

    int frame_count = 0;
    uint8_t score   = 0;
    Display_print_header(&next_block, score);
    bool run = true;
    while (run)
    {
        run = Display_update_arena(arena_vec, &curr_block);
        usleep(10000);

        if (frame_count++ >= 100)
        {
            frame_count                 = 0;
            uint8_t last_complete_row = 0;
            if (is_touchdown(arena_vec, &curr_block))
            {
                Arena_add_block(arena_vec, &curr_block, '0');
                curr_block = next_block;
                next_block = Block_new();

                int num_of_complete_rows = Arena_cleanup_and_get_points(arena_vec, &last_complete_row);
                score += num_of_complete_rows * num_of_complete_rows;
                for (uint8_t i = 0; i < num_of_complete_rows; i++)
                {
                    Display_color_arena_row(arena_vec, last_complete_row - i);
                }
                for (uint8_t i = 0; i < num_of_complete_rows; i++)
                {
                    Arena_remove_row(arena_vec, last_complete_row);
                }
                Display_print_header(&next_block, score);
                if (is_touchdown(arena_vec, &curr_block))
                {
                    printf("\e[33mGAME OVER\e[0m - PRESS ESC TO QUIT\n");
                    break;
                }
                continue;
            }
            Block_move(&curr_block, DOWN);
        }
    }

    pthread_join(keyboard_t, NULL);
    exit_game();

    return 0;
}

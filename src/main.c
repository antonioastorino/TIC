#include "class_arena.h"
#include "class_tetromino.h"
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
    Tetromino curr_tetromino = Tetromino_new();
    Tetromino next_tetromino = Tetromino_new();

    int frame_count = 0;
    uint8_t score   = 0;
    Display_print_header(&next_tetromino, score);
    bool run = true;
    while (run)
    {
        run = Display_update_arena(arena_vec, &curr_tetromino);
        usleep(10000);

        if (frame_count++ >= 100)
        {
            frame_count                = 0;
            uint8_t complete_row_vec[4] = {0};
            if (is_touchdown(arena_vec, &curr_tetromino))
            {
                Arena_add_tetromino(arena_vec, &curr_tetromino, '0');
                curr_tetromino = next_tetromino;
                next_tetromino = Tetromino_new();

                int num_of_complete_rows
                    = Arena_cleanup_and_get_points(arena_vec, complete_row_vec);
                score += num_of_complete_rows * num_of_complete_rows;
                for (uint8_t i = 0; i < num_of_complete_rows; i++)
                {
                    Display_color_arena_row(arena_vec, complete_row_vec[i]);
                }
                for (uint8_t i = 0; i < num_of_complete_rows; i++)
                {
                    // Remove rows from the top to the bottom so that the nex row to be removed is
                    // not shifted and its index is still valid.
                    Arena_remove_row(arena_vec, complete_row_vec[i]);
                }
                Display_print_header(&next_tetromino, score);
                if (is_touchdown(arena_vec, &curr_tetromino))
                {
                    printf("\e[33mGAME OVER\e[0m - PRESS ESC TO QUIT\n");
                    break;
                }
                continue;
            }
            Tetromino_move(&curr_tetromino, DOWN);
        }
    }

    pthread_join(keyboard_t, NULL);
    exit_game();

    return 0;
}

#include "class_playground.h"
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
    Playground_init(playground_vec);
    pthread_t keyboard_t;
    void* fn = Keyboard_listen;
    pthread_create(&keyboard_t, NULL, fn, NULL);

    srand(time(0));
    Tetromino curr_tetromino = Tetromino_new();
    Tetromino next_tetromino = Tetromino_new();

    uint16_t frame_count                 = 0;
    uint64_t score                       = 0;
    uint16_t level_score                 = 0;
    uint16_t gravity_rate                = 1000;
    uint16_t curr_level                  = 0;
    const uint16_t level_score_threshold = 40;
    Display_print_header(&next_tetromino, score, curr_level);
    bool run = true;
    while (run)
    {
        run = Display_update_playground(playground_vec, &curr_tetromino);
        usleep(1000);

        if (frame_count++ >= gravity_rate)
        {
            frame_count                 = 0;
            uint8_t complete_row_vec[4] = {0};
            if (is_touchdown(playground_vec, &curr_tetromino))
            {
                Playground_add_tetromino(playground_vec, &curr_tetromino, '0');
                curr_tetromino = next_tetromino;
                next_tetromino = Tetromino_new();

                int num_of_complete_rows
                    = Playground_cleanup_and_get_points(playground_vec, complete_row_vec);
                int points = num_of_complete_rows * num_of_complete_rows;
                level_score += points;
                score += points;
                for (uint8_t i = 0; i < num_of_complete_rows; i++)
                {
                    Display_color_playground_row(playground_vec, complete_row_vec[i]);
                }
                for (uint8_t i = 0; i < num_of_complete_rows; i++)
                {
                    // Remove rows from the top to the bottom so that the nex row to be removed is
                    // not shifted and its index is still valid.
                    Playground_remove_row(playground_vec, complete_row_vec[i]);
                }
                Display_print_header(&next_tetromino, score, curr_level);
                if (is_touchdown(playground_vec, &curr_tetromino))
                {
                    printf("\e[33mGAME OVER\e[0m - PRESS ESC TO QUIT\n");
                    break;
                }
                if (level_score >= level_score_threshold)
                {
                    // Level completed - reset the playground
                    curr_level++;
                    level_score = score % level_score_threshold;
                    gravity_rate *= 0.85;
                    Display_print_header(&next_tetromino, score, curr_level);
                    Playground_init(playground_vec);
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

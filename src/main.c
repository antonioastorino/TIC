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
#include "class_arena.h"

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
    Arena_init(arena_vec);
    pthread_t keyboard_t;
    void* fn = Keyboard_listen;
    pthread_create(&keyboard_t, NULL, fn, NULL);
   
    srand(time(0));
    Block curr_block = Block_new();
    Block next_block = Block_new();

    int frame_count = 0;
    uint8_t score   = 0;
    bool run = true;
    while (run)
    {
        run = Display_update(arena_vec, &curr_block, &next_block, score);
        usleep(10000);

        if (frame_count++ >= 100)
        {
            frame_count = 0;
            if (is_touchdown(arena_vec, &curr_block))
            {
                Arena_add_block(arena_vec, &curr_block, '0');
                curr_block = next_block;
                next_block = Block_new();
                score += Arena_cleanup_and_get_points(arena_vec);
                continue;
            }
            Block_move(&curr_block, DOWN);
        }
    }

    pthread_join(keyboard_t, NULL);
    exit_game();

    return 0;
}

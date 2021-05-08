#include "display.h"
#include "logger.h"

char get_char_at(char* buffer, int8_t x, int8_t y) { 
    LOG_DEBUG("Getting char at (%d, %d)", x, y);
    return buffer[x * COLS + y];
    }

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
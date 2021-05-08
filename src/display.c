#include "display.h"

char get_char_at(char* buffer, int8_t x, int8_t y) { return buffer[x * COLS + y]; }

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
#include "keyboard.h"
#include <termios.h>


struct termios initial_settings;

void Keyboard_init() {
    struct termios settings;

    if (tcgetattr(0, &settings) < 0) {
		return;
	}
    initial_settings = settings;

    settings.c_lflag &= ~ICANON;
    settings.c_lflag &= ~ECHO;
    settings.c_lflag &= ~ISIG;
    settings.c_cc[VMIN]  = 1;
    settings.c_cc[VTIME] = 0;

    tcsetattr(0, TCSANOW, &settings);
}

void Keyboard_reset() { tcsetattr(0, TCSANOW, &initial_settings); }

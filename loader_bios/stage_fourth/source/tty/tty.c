#include <tty.h>

size_t TTY_NUM_CHARS_PER_LINE = 80;
size_t TTY_NUM_LINES = 25;
size_t TTY_TARGET_GLYPH_WIDTH = 8;
size_t TTY_TARGET_GLYPH_HEIGHT = 8;
size_t TTY_SPACING_X = 1;
size_t TTY_SPACING_Y = 2;
size_t TTY_CELL_X = 9;
size_t TTY_CELL_Y = 10;

size_t TTY_POSITION = 0;
size_t TTY_MAX_POSITION = 80 * 25 - 1;

uint8_t TTY_BKG_RED = 0;
uint8_t TTY_BKG_GREEN = 0;
uint8_t TTY_BKG_BLUE = 0;
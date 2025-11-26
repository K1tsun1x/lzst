#include <tty/tty.h>

extern uint8_t TTY_BKG_RED;
extern uint8_t TTY_BKG_GREEN;
extern uint8_t TTY_BKG_BLUE;

void tty_scroll_down(size_t num_lines) {
	return tty_scroll_down_color(
		num_lines,
		TTY_BKG_RED, TTY_BKG_GREEN, TTY_BKG_BLUE
	);
}
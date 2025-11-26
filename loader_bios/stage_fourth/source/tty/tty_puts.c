#include <tty/tty.h>

extern uint8_t TTY_FRG_RED;
extern uint8_t TTY_FRG_GREEN;
extern uint8_t TTY_FRG_BLUE;
extern uint8_t TTY_BKG_RED;
extern uint8_t TTY_BKG_GREEN;
extern uint8_t TTY_BKG_BLUE;

int tty_puts(const char* s) {
	return tty_puts_color(
		s,
		TTY_FRG_RED, TTY_FRG_GREEN, TTY_FRG_BLUE,
		TTY_BKG_RED, TTY_BKG_GREEN, TTY_BKG_BLUE
	);
}
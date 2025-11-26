#include <tty/tty.h>

extern uint8_t TTY_FRG_RED;
extern uint8_t TTY_FRG_GREEN;
extern uint8_t TTY_FRG_BLUE;
extern uint8_t TTY_BKG_RED;
extern uint8_t TTY_BKG_GREEN;
extern uint8_t TTY_BKG_BLUE;

int tty_putchar(int c) {
	return tty_putchar_color(
		c,
		TTY_FRG_RED, TTY_FRG_GREEN, TTY_FRG_BLUE,
		TTY_BKG_RED, TTY_BKG_GREEN, TTY_BKG_BLUE
	);
}
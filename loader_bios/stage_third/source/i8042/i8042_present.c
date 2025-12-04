#include <i8042.h>

bool i8042_present(void) {
	bool res = true;

	i8042_disable_kbd();
	i8042_disable_mouse();
	i8042_flush_buf();

	uint8_t s1 = i8042_read_status();
	uint8_t s2 = i8042_read_status();
	if (s1 == s2 && (s1 == 0 || s1 == 0xff)) res = false;

	i8042_enable_kbd();
	i8042_enable_mouse();
	return res;
}
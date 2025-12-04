#include <i8042.h>

extern spinlock_t __I8042_SPINLOCK;

void i8042_set_a20_state(bool enabled) {
	i8042_disable_kbd();
	i8042_disable_mouse();
	i8042_flush_buf();

	uint8_t ctrlout = i8042_read_cntrl_out();
	if (enabled) ctrlout |= I8042_CONTROLLER_OUTPUT_A20_GATE;
	else ctrlout &= ~I8042_CONTROLLER_OUTPUT_A20_GATE;
	i8042_write_cntrl_out(ctrlout);
	
	i8042_enable_kbd();
	i8042_enable_mouse();
}
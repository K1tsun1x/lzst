#include <a20.h>

spinlock_t __A20_SPINLOCK = SPINLOCK_INIT;

bool a20_set_fast_gate_state(bool enabled) {
	spinlock_acquire(&__A20_SPINLOCK);			// FIXME: makes no sense in single threaded mode

	uint8_t value = inb(A20_PORT_FAST_GATE);
	if (!!(value & A20_FAST_GATE_ENABLE) == enabled) {
		spinlock_release(&__A20_SPINLOCK);
		return false;
	}

	value &= ~A20_FAST_GATE_RESET_CPU;
	if (enabled) value |= A20_FAST_GATE_ENABLE;
	else value &= ~A20_FAST_GATE_ENABLE;
	outb(A20_PORT_FAST_GATE, value);
	io_wait();

	spinlock_release(&__A20_SPINLOCK);			// FIXME: makes no sense in single threaded mode
	return true;
}
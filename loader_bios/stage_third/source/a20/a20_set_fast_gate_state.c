#include <a20.h>

bool a20_set_fast_gate_state(bool enabled) {
	uint8_t value = inb(A20_PORT_FAST_GATE);
	if (!!(value & A20_FAST_GATE_ENABLE) == enabled) return false;

	value &= ~A20_FAST_GATE_RESET_CPU;
	if (enabled) value |= A20_FAST_GATE_ENABLE;
	else value &= ~A20_FAST_GATE_ENABLE;
	outb(A20_PORT_FAST_GATE, value);
	io_wait();
	return true;
}
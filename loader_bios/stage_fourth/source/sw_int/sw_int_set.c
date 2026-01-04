#include <sw_int/sw_int.h>

XTRN_ONLY_CPP sw_int_handler_t SW_INT_HANDLERS[NUM_SW_INTS] = { 0 };

bool sw_int_set(size_t sw_int, sw_int_handler_t handler) {
	if (sw_int >= NUM_SW_INTS) return false;

	SW_INT_HANDLERS[sw_int] = handler;
	return true;
}
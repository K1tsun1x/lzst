#include <sw_int/sw_int.h>

XTRN_C sw_int_handler_t SW_INT_HANDLERS[NUM_SW_INTS];

bool sw_int_get(size_t sw_int, sw_int_handler_t* handler) {
	if (sw_int >= NUM_SW_INTS || !handler) return false;

	*handler = SW_INT_HANDLERS[sw_int];
	return true;
}
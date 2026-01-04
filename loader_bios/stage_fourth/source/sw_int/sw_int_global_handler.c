#include <sw_int/sw_int.h>

XTRN_C sw_int_handler_t SW_INT_HANDLERS[NUM_SW_INTS];

XTRN_C void sw_int_global_handler(bool ring_switch, sw_int_data_t* data) {
	const size_t sw_int = data->int_index - 0x40;
	if (sw_int >= NUM_SW_INTS) return;

	if (SW_INT_HANDLERS[sw_int]) SW_INT_HANDLERS[sw_int](ring_switch, data);
}
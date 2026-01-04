#include <sw_int/sw_int.h>

XTRN_C void LOADERCALL sw_int_stub0(void);
XTRN_C void LOADERCALL sw_int_stub1(void);

XTRN_C void sw_int_scheduler_yield(bool ring_switch, sw_int_data_t* data);
XTRN_C void sw_int_tty(bool ring_switch, sw_int_data_t* data);

void sw_int_init(void) {
	idt32_set_entry(IDT_SW_INT_SCHEDULER_YIELD_VECTOR, (uint32_t)sw_int_stub0, 0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT | IDT_FLAG_DPL0 | IDT_FLAG_DPL1);
	idt32_set_entry(IDT_SW_INT_TTY_VECTOR, (uint32_t)sw_int_stub1, 0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT | IDT_FLAG_DPL0 | IDT_FLAG_DPL1);

	sw_int_set(SW_INT_SCHEDULER_YIELD, sw_int_scheduler_yield);
	sw_int_set(SW_INT_TTY, sw_int_tty);
}
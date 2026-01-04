#include <sw_int/sw_int.h>

XTRN_C void sw_int_tty(bool ring_switch, sw_int_data_t* data) {
	UNREFERENCED_PARAMETER(ring_switch);
	
	switch (data->def_regs.ax) {
		case SW_INT_TTY_FUNCTION_PUTCHAR: {
			tty_putchar((char)(data->def_regs.cx & 0xff));
			break;
		}

		case SW_INT_TTY_FUNCTION_PUTS: {
			// FIXME: invalid memory (trying to read from other page directory)
			tty_puts((char*)data->def_regs.cx);
			break;
		}
	}
}
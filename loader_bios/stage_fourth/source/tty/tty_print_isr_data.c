#include <tty/tty.h>

int tty_print_isr_data(const isr_data_t* isr_data) {
	int res = tty_printf("AX = %#010x, CX = %#010x\n", isr_data->ax, isr_data->cx);
	res += tty_printf("DX = %#010x, BX = %#010x\n", isr_data->dx, isr_data->bx);
	res += tty_printf("SI = %#010x, DI = %#010x\n", isr_data->si, isr_data->di);
	res += tty_printf("SP = %#010x, BP = %#010x\n", isr_data->sp, isr_data->bp);
	res += tty_printf("DS = %#010x, ES = %#010x\n", isr_data->ds, isr_data->es);
	res += tty_printf("FS = %#010x, GS = %#010x\n", isr_data->fs, isr_data->gs);
	res += tty_printf("INT #%#010x, ERR #%#010x\n", isr_data->int_index, isr_data->error_code);
	res += tty_printf("CS = %#010x, IP = %#010x\n", isr_data->cs, isr_data->ip);
	res += tty_printf("FLAGS = %#010x\n", isr_data->flags);
	return res;
}
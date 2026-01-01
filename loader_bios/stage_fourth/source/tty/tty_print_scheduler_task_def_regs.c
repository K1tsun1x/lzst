#include <tty/tty.h>

int tty_print_scheduler_task_def_regs(const scheduler_task_def_regs_t* def_regs) {
	int res = tty_printf("AX = %#010x, CX = %#010x\n", def_regs->ax, def_regs->cx);
	res += tty_printf("DX = %#010x, BX = %#010x\n", def_regs->dx, def_regs->bx);
	res += tty_printf("SI = %#010x, DI = %#010x\n", def_regs->si, def_regs->di);
	res += tty_printf("SP = %#010x, BP = %#010x\n", def_regs->sp, def_regs->bp);
	res += tty_printf("SS = %#010x, DS = %#010x\n", def_regs->ss, def_regs->ds);
	res += tty_printf("CS = %#010x, IP = %#010x\n", def_regs->cs, def_regs->ip);
	res += tty_printf("FLAGS = %#010x\n", def_regs->flags);
	return res;
}
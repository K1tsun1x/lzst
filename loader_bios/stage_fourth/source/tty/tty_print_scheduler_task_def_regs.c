#include <tty/tty.h>

int tty_print_scheduler_task_def_regs(const scheduler_task_def_regs_t* def_regs) {
	int res = tty_printf("AX:\t%#010x, CX:\t\t%#010x\n", def_regs->ax, def_regs->cx);
	res += tty_printf("DX:\t%#010x, BX:\t\t%#010x\n", def_regs->dx, def_regs->bx);
	res += tty_printf("SI:\t%#010x, DI:\t\t%#010x\n", def_regs->si, def_regs->di);
	res += tty_printf("SP:\t%#010x, BP:\t\t%#010x\n", def_regs->sp, def_regs->bp);
	res += tty_printf("SS:\t%#010x, DS:\t\t%#010x\n", def_regs->ss, def_regs->ds);
	res += tty_printf("CS:\t%#010x, IP:\t\t%#010x\n", def_regs->cs, def_regs->ip);
	res += tty_printf("CR3:%#010x, FLAGS:\t%#010x\n", def_regs->cr3, def_regs->flags);
	return res;
}
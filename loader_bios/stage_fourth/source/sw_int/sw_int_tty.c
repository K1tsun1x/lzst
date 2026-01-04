#include <sw_int/sw_int.h>

XTRN_C void sw_int_tty(bool ring_switch, sw_int_data_t* data) {
	UNREFERENCED_PARAMETER(ring_switch);
	
	switch (data->def_regs.ax) {
		case SW_INT_TTY_FUNCTION_PUTCHAR: {
			tty_putchar((char)(data->def_regs.cx & 0xff));
			data->def_regs.ax = STATUS_OK;
			break;
		}

		case SW_INT_TTY_FUNCTION_PUTS: {
			const paging_pde_t* src_dir = (paging_pde_t*)(data->def_regs.cr3 & PAGING_MASK_PDE_ADDRESS);

			const size_t len = vmm_get_far_ansi_str_len(src_dir, data->def_regs.cx, SW_INT_TTY_MAX_STR_LEN);
			if (len == SIZE_MAX) {
				data->def_regs.ax = STATUS_INVALID_PARAMETER_2;
				return;
			}

			char* tmp = (char*)pmm_allocate_memory(len + 1, 0);
			if (!tmp) {
				data->def_regs.ax = STATUS_NO_MEMORY;
				return;
			}

			if (!vmm_copy_memory_from(src_dir, tmp, data->def_regs.cx, len)) {
				pmm_free_memory(tmp);
				data->def_regs.ax = STATUS_INVALID_PARAMETER_2;
				return;
			}

			tmp[len] = '\0';

			tty_puts(tmp);
			pmm_free_memory(tmp);
			data->def_regs.ax = STATUS_OK;
			break;
		}

		default: {
			data->def_regs.ax = STATUS_INVALID_PARAMETER_1;
			return;
		}
	}
}
#include <main/main.h>

XTRN_C uint32_t test_task1[];
XTRN_C uint32_t test_task2[];

void map_simple_task(
	paging_pde_t* task_dir,

	uintptr_t kernel_base,
	size_t kernel_size,

	uintptr_t kernel_stack_bottom,
	size_t kernel_stack_size,

	uintptr_t task_phys_addr,
	uintptr_t task_virt_addr,
	size_t task_size
	
	// , uintptr_t task_stack_bottom_phys_addr,
	// uintptr_t task_stack_bottom_virt_addr,
	// size_t task_stack_size
) {
	// map page directory

	if (!paging_map_pages(
		task_dir,
		(uintptr_t)task_dir, 0,
		ALIGN_UP_P2(PAGING_DIRECTORY_SIZE, VMM_PAGE_SIZE) / VMM_PAGE_SIZE,
		PAGING_PDE_FLAG_PRESENT | PAGING_PDE_FLAG_READ_WRITE | PAGING_PDE_FLAG_USER_SUPERVISOR
	)) {
		tty_prints_negative("Error: failed to map page dir for task!\n");
		panic_halt();
	}

	// map kernel

	if (!paging_map_pages(
		task_dir,
		kernel_base,
		kernel_base,
		ALIGN_UP_P2(kernel_size, VMM_PAGE_SIZE) / VMM_PAGE_SIZE,
		PAGING_PDE_FLAG_PRESENT | PAGING_PDE_FLAG_READ_WRITE | PAGING_PDE_FLAG_USER_SUPERVISOR
	)) {
		tty_prints_negative("Error: failed to map kernel for task!\n");
		panic_halt();
	}

	// map kernel stack

	if (!paging_map_pages(
		task_dir,
		kernel_stack_bottom,
		kernel_stack_bottom,
		ALIGN_UP_P2(kernel_stack_size, VMM_PAGE_SIZE) / VMM_PAGE_SIZE,
		PAGING_PDE_FLAG_PRESENT | PAGING_PDE_FLAG_READ_WRITE | PAGING_PDE_FLAG_USER_SUPERVISOR
	)) {
		tty_prints_negative("Error: failed to map kernel stack for task!\n");
		panic_halt();
	}

	// map task code sections

	if (!paging_map_pages(
		task_dir,
		task_phys_addr,
		task_virt_addr,
		ALIGN_UP_P2(task_size, VMM_PAGE_SIZE) / VMM_PAGE_SIZE,
		PAGING_PDE_FLAG_PRESENT | PAGING_PDE_FLAG_READ_WRITE | PAGING_PDE_FLAG_USER_SUPERVISOR
	)) {
		tty_prints_negative("Error: failed to map code section for task!\n");
		panic_halt();
	}

	// map stack

	/*
	if (!paging_map_pages(
		task_dir,
		task_stack_bottom_phys_addr,
		task_stack_bottom_virt_addr,
		ALIGN_UP_P2(task_stack_size, VMM_PAGE_SIZE) / VMM_PAGE_SIZE,
		PAGING_PDE_FLAG_PRESENT | PAGING_PDE_FLAG_READ_WRITE
	)) {
		tty_prints_negative("Error: failed to map stack for task!\n");
		panic_halt();
	}
	*/
}

void stage_fourth_startup(boot_info_t* bootloader_info) {
	// NULL
	gdt_init32(&GDT[0], 0, 0, 0, 0);

	// kernel code
	gdt_init32(
		&GDT[1],
		0xfffff, 0,
		GDT_ACCESS_READABLE_WRITEABLE | GDT_ACCESS_EXECUTABLE | GDT_ACCESS_NOT_SYSTEM | GDT_ACCESS_PRESENT,
		GDT_FLAG_SIZE | GDT_FLAG_GRANULARITY
	);

	// kernel data
	gdt_init32(
		&GDT[2],
		0xfffff, 0,
		GDT_ACCESS_READABLE_WRITEABLE | GDT_ACCESS_NOT_SYSTEM | GDT_ACCESS_PRESENT,
		GDT_FLAG_SIZE | GDT_FLAG_GRANULARITY
	);

	// user code
	gdt_init32(
		&GDT[3],
		0xfffff, 0,
		GDT_ACCESS_READABLE_WRITEABLE | GDT_ACCESS_EXECUTABLE | GDT_ACCESS_NOT_SYSTEM | GDT_ACCESS_DPL0 | GDT_ACCESS_DPL1 | GDT_ACCESS_PRESENT,
		GDT_FLAG_SIZE | GDT_FLAG_GRANULARITY
	);

	// user data
	gdt_init32(
		&GDT[4],
		0xfffff, 0,
		GDT_ACCESS_READABLE_WRITEABLE | GDT_ACCESS_NOT_SYSTEM | GDT_ACCESS_DPL0 | GDT_ACCESS_DPL1 | GDT_ACCESS_PRESENT,
		GDT_FLAG_SIZE | GDT_FLAG_GRANULARITY
	);

	// TSS
	gdt_init32(
		&GDT[5],
		sizeof(TSS) - 1, (uintptr_t)&TSS,
		0x89,
		0
	);

	GDTR.offset = (uintptr_t)&GDT[0];
	GDTR.size = sizeof(GDT) - 1;

	gdtr_load(&GDTR);

	TSS.esp0 = 0x6000;
	TSS.ss0 = 0x10;
	TSS.iopb = sizeof(TSS);
	__asm__ __volatile__("ltr %%ax"::"a"(0x28));

	exceptions_init();
	irqs_init();
	idt32_init();

	sw_int_init();

	const uintptr_t kernel_base = (uintptr_t)&__PTR_BASE__;
	const uintptr_t kernel_end = (uintptr_t)&__PTR_END__;
	const uintptr_t kernel_size = kernel_end - kernel_base;

	sys_init(
		&bootloader_info->video_mode,
		bootloader_info->vga_present,
		bootloader_info->vbe_present,
		bootloader_info->i8042_present
	);

	sys_info_t sys_info;
	sys_get_info(&sys_info);

	gfx_init(&sys_info.video_mode);
	tty_init(80, 25, 2, 2, GFX_UNPACK_COLOR(GFX_COLOR_LIGHT_GRAY), 0x18, 0x18, 0x18);

	if (!sys_info.cpuid_present) {
		// FIXME: not implemented yet...
		tty_prints_negative("Error: machine without CPUID is not supported");
		panic_halt();
	}
	else if (!sys_info.fpu_present) {
		// FIXME: not implemented yet...
		tty_prints_negative("Error: machine without x87 FPU is not supported");
		panic_halt();
	}

	const size_t w = sys_info.video_mode.width;
	const size_t h = sys_info.video_mode.height;
	const float aspect = (float)w / (float)h;

	size_t num_chars_per_line = w / 14;
	size_t num_lines = h / 18;

	if (aspect > 1.6f && num_chars_per_line < 100) num_chars_per_line = 100;
	if (aspect < 1.3f && num_chars_per_line > 80) num_chars_per_line = 80;

	// very small screen
	if (w < 640 || h < 480) {
		if (num_chars_per_line > 40) num_chars_per_line = 40;
		if (num_lines > 20) num_lines = 20;
	}

	tty_init(num_chars_per_line, num_lines, 2, 2, GFX_UNPACK_COLOR(GFX_COLOR_LIGHT_GRAY), 0x18, 0x18, 0x18);

	tty_puts_color(
		"Welcome to LZST bootloader!",
		0xff, 0x7f, 0,
		0x18, 0x18, 0x18
	);

	tty_printf("Boot drive:\t\t\t\t\x1b[94m%#x\x1b[0m\n", bootloader_info->boot_drive);

	const e820_reg_t RESERVED_REGS[] = {
		{	// IVT, BDA + kernel stack
			0x0000000000000000,
			0x0000000000100000,
			E820_REG_TYPE_RESERVED
		},
		{	// Video, EBDA, BIOS ROM (16-bit)
			0x0000000000080000,
			0x0000000000080000,
			E820_REG_TYPE_RESERVED
		},
		{	// ISA hole
			0x0000000000f00000,
			0x0000000000100000,
			E820_REG_TYPE_RESERVED
		},
		{	// PCI, MMIO, ...
			0x00000000c0000000,
			0x0000000040000000,
			E820_REG_TYPE_RESERVED
		},
		{	// BIOS ROM (64-bit)
			0x00000000ff000000,
			0x0000000001000000,
			E820_REG_TYPE_RESERVED
		},
		{	// The fourth stage
			(uint64_t)kernel_base,
			(uint64_t)kernel_size,
			E820_REG_TYPE_RESERVED
		},
		{	// Framebuffer
			(uint64_t)(uintptr_t)GFX_VIDEO_MODE.framebuffer,
			(uint64_t)(GFX_VIDEO_MODE.height * ((GFX_VIDEO_MODE.depth + 7) / 8) * GFX_VIDEO_MODE.pitch),
			E820_REG_TYPE_RESERVED
		}
	};
	
	sys_info.memory_map_length = pmm_init(
		bootloader_info->memory_map,
		bootloader_info->memory_map_length,
		RESERVED_REGS,
		sizeof(RESERVED_REGS) / sizeof(RESERVED_REGS[0])
	);

	sys_set_info(&sys_info);

	if (PMM_FIRST_REGION_BASE_ADDRESS == 0) {
		tty_prints_negative("Error: not enough memory!");
		panic_halt();
	}

	tty_puts("Normalized usable memory map:");
	pmm_reg_t* first_pmm_reg = (pmm_reg_t*)PMM_FIRST_REGION_BASE_ADDRESS;
	do {
		tty_printf(
			"Base: \x1b[96m%#010x\x1b[0m, Length: \x1b[96m%#010x\x1b[0m, Pages: \x1b[96m%xh\x1b[0m\n",
			// (uint32_t)(first_pmm_reg->base_address >> 32),
			(uint32_t)(first_pmm_reg->base_address & 0xffffffff),
			// (uint32_t)(first_pmm_reg->length >> 32),
			(uint32_t)(first_pmm_reg->length & 0xffffffff),
			(uint32_t)first_pmm_reg->num_free_pages,
			(uint32_t)(first_pmm_reg->next_reg_address)
		);

		first_pmm_reg = (pmm_reg_t*)(uintptr_t)first_pmm_reg->next_reg_address;
	} while(first_pmm_reg != NULL);

	tty_prints("VGA:\t\t\t\t\t");
	if (sys_info.vga_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nVBE:\t\t\t\t\t");
	if (sys_info.vbe_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\ni8042 controller:\t\t");
	if (sys_info.i8042_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nCPUID:\t\t\t\t\t");
	if (sys_info.cpuid_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nFPU:\t\t\t\t\t");
	if (sys_info.fpu_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nSSE version:\t\t\t");
	if (!sys_info.sse_version) tty_prints_neutral("[NONE]");
	else {
		if (sys_info.sse_version < 0x10) tty_printf("\x1b[92m%u\x1b[0m", sys_info.sse_version);
		else {
			if (sys_info.sse_version == 0x41) tty_printf("\x1b[92m4.1\x1b[0m");
			else if (sys_info.sse_version == 0x42) tty_printf("\x1b[92m4.2\x1b[0m");
			else tty_printf("\x1b[92m4.2+\x1b[0m");
		}
	}
	
	tty_prints("\nAVX:\t\t\t\t\t");
	if (sys_info.avx_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nOSXSAVE:\t\t\t\t");
	if (sys_info.osxsave_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nAPIC:\t\t\t\t\t");
	if (sys_info.apic_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nMSR:\t\t\t\t\t");
	if (sys_info.msr_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_printf(
		"\nVideo:\t\t\t\t\tmode=\x1b[96m%xh\x1b[0m (\x1b[96m%u\x1b[0mx\x1b[96m%u\x1b[0m \x1b[94m%ubpp\x1b[0m)\n",
		sys_info.video_mode.number,
		sys_info.video_mode.width,
		sys_info.video_mode.height,
		sys_info.video_mode.depth
	);

	status_t status = sys_parse_acpi_tables(&sys_info);
	if (status != STATUS_OK) {
		if (status == STATUS_NOT_FOUND) tty_prints_negative("Error: unable to find RSDP");
		else if (status == STATUS_INVALID_HEADER) tty_prints_negative("Error: invalid RSDT header");
		else if (status == STATUS_UNREACHABLE) tty_prints_negative("Error: RSDT unreachable");
		else if (status == STATUS_NO_MEMORY) tty_prints_negative("Error: not enough memory");
		panic_halt();
	}

	sys_set_info(&sys_info);

	tty_printf("RSDP:\t\t\t\t\t\x1b[96m%#010x\x1b[0m\n", sys_info.acpi_rsdp_address);
	tty_printf("RSDT:\t\t\t\t\t\x1b[96m%#010x\x1b[0m\n", sys_info.acpi_rsdt_address);
	tty_printf("FADT:\t\t\t\t\t\x1b[96m%#010x\x1b[0m\n", sys_info.acpi_fadt_address);
	tty_printf("MADT:\t\t\t\t\t\x1b[96m%#010x\x1b[0m\n", sys_info.acpi_madt_address);

	tty_prints("Interrupt Controller:\t");
	if (sys_info.apic_present) {
		tty_prints_positive("APIC");
		pic_mask_all_irqs();
		lapic_init();

		tty_puts("\nLAPICs:");
		for (size_t i = 0; i < sys_info.num_lapics; i++) {
			tty_printf(
				"%u) Processor ID=\x1b[96m%#04x\x1b[0m, APIC ID=\x1b[96m%#04x\x1b[0m, BSP=\x1b[96m%u\x1b[0m\n",
				i + 1,
				sys_info.lapics[i].acpi_processor_id,
				sys_info.lapics[i].apic_id,
				sys_info.lapics[i].bsp
			);
		}

		tty_puts("I/O APICs:");
		for (size_t i = 0; i < sys_info.num_ioapics; i++) {
			tty_printf(
				"%u) I/O APIC ID=\x1b[96m%#04x\x1b[0m, Base=\x1b[96m%#010x\x1b[0m, GSIB=\x1b[96m%#010x\x1b[0m\n",
				i + 1,
				sys_info.ioapics[i].ioapic_id,
				sys_info.ioapics[i].ioapic_base,
				sys_info.ioapics[i].ioapic_gsib
			);

			if (
				sys_info.ioapics[i].ioapic_gsib <= 0 &&
				0 < sys_info.ioapics[i].ioapic_gsib + 24
			) ioapic_init(sys_info.ioapics[i].ioapic_base);
		}

		tty_puts("I/O APIC Interrupt Source Overrides:");
		for (size_t i = 0; i < sys_info.num_ioapic_isos; i++) {
			tty_printf(
				"%u) Bus=\x1b[96m%xh\x1b[0m, IRQ=\x1b[96m%02xh\x1b[0m, GSI=\x1b[96m%#010x\x1b[0m\n",
				i + 1,
				sys_info.ioapic_isos[i].bus,
				sys_info.ioapic_isos[i].irq,
				sys_info.ioapic_isos[i].gsi
			);

			if (i >= NUM_IRQS) continue;
			
			sys_info_ioapic_iso_t* ioapiciso = &sys_info.ioapic_isos[i];
			irq_info_t irq_info;
			irq_get_info(ioapiciso->irq, &irq_info);
			irq_info.irq_remapped = (uint8_t)ioapiciso->gsi;

			if (ioapiciso->flags & 8) irq_info.trigger_mode = IRQ_INFO_TRIGGER_MODE_LEVEL;
			else irq_info.trigger_mode = IRQ_INFO_TRIGGER_MODE_EDGE;

			if (ioapiciso->flags & 2) irq_info.polarity = IRQ_INFO_POLARITY_ACTIVE_LOW;
			else irq_info.polarity = IRQ_INFO_POLARITY_ACTIVE_HIGH;

			irq_set_info(ioapiciso->irq, &irq_info);
		}

		virt_int_ctrl_mask_irq = ioapic_mask_irq;
		virt_int_ctrl_unmask_irq = ioapic_unmask_irq;
		virt_int_ctrl_mask_all_irqs = ioapic_mask_all_irqs;
		virt_int_ctrl_unmask_all_irqs = ioapic_unmask_all_irqs;
		virt_int_ctrl_eoi = lapic_send_eoi;
	}
	else {
		tty_prints_positive("PIC");
		pic_init();
		
		virt_int_ctrl_mask_irq = pic_mask_irq;
		virt_int_ctrl_unmask_irq = pic_unmask_irq;
		virt_int_ctrl_mask_all_irqs = pic_mask_all_irqs;
		virt_int_ctrl_unmask_all_irqs = pic_unmask_all_irqs;
		virt_int_ctrl_eoi = pic_send_eoi;
	}

	virt_int_ctrl_mask_all_irqs();
	sti();

	tty_prints("\nTimers:\t\t\t\t\t");
	uint8_t timer_vector;
	if (sys_info.apic_present) {
		tty_prints_positive("LAPIC, PIT\n");

		irq_info_t pit_irq_info;
		irq_get_info(PIT_IRQ, &pit_irq_info);
		irq_set(PIT_IRQ, virt_timer_irq_handler);
		irq_set(LAPIC_TIMER_VECTOR - 32, virt_timer_irq_handler);
		virt_int_ctrl_unmask_irq(pit_irq_info.irq_remapped);

		lapic_timer_init(LAPIC_TIMER_VECTOR, TIMER_TICK_MS);

		virt_int_ctrl_mask_irq(pit_irq_info.irq_remapped);
		irq_set(LAPIC_TIMER_VECTOR - 32, NULL);
		irq_set(PIT_IRQ, NULL);

		timer_vector = LAPIC_TIMER_VECTOR;
		scheduler_init(LAPIC_TIMER_VECTOR);
	}
	else {
		tty_prints_positive("PIT\n");
		
		irq_info_t pit_irq_info;
		irq_get_info(PIT_IRQ, &pit_irq_info);
		
		pit_init(PIT_COMMAND_SQUARE_WAVE, PIT_COMMAND_CHNL0, TIMER_TICK_MS);

		virt_int_ctrl_unmask_irq(pit_irq_info.irq_remapped);

		timer_vector = 32 + pit_irq_info.irq_remapped;
		scheduler_remap(32 + pit_irq_info.irq_remapped);
	}

	virt_timer_set_tick_ms(TIMER_TICK_MS);

	tty_prints("Scheduler:\t\t\t\t");
	status = scheduler_init(timer_vector);
	if (status == STATUS_OK) tty_prints_positive("[INITIALIZED]\n");
	else {
		tty_prints_negative("[NOT INITIALIZED]\n");
		tty_printf("\x1b[91mError: failed to init scheduler (status: %?)!\n", status);
		panic_halt();
	}

	tty_prints("Paging:\t\t\t\t\t");
	// Identity mapping (1:1)
	memset(&PDE[0], 0, sizeof(PDE));
	if (!paging_map_pages(PDE, 0, 0, 0x100000, PAGING_PTE_FLAG_PRESENT | PAGING_PTE_FLAG_READ_WRITE)) {
		tty_prints_negative("[NOT ENABLED]\n");
		tty_prints_negative("Error: failed to set identity mapping (1:1)!\n");
		panic_halt();
	}
	paging_load_directory(PDE);
	paging_enable();

	tty_prints_positive("[ENABLED]\n");

	paging_pde_t* task1_dir = (paging_pde_t*)pmm_allocate_memory(PAGING_DIRECTORY_SIZE, PMM_MEM_FLAG_ZEROED);
	paging_pde_t* task2_dir = (paging_pde_t*)pmm_allocate_memory(PAGING_DIRECTORY_SIZE, PMM_MEM_FLAG_ZEROED);
	if (!task1_dir || !task2_dir) {
		tty_prints_negative("Error: failed to allocate page dir(s) for task(s)!\n");
		panic_halt();
	}

	const uintptr_t tt1 = (uintptr_t)&test_task1;
	const uintptr_t tt2 = (uintptr_t)&test_task2;
	map_simple_task(task1_dir, kernel_base, kernel_size, 0x4000, 0x2000, tt1, 0x400000, 0x1000);
	map_simple_task(task2_dir, kernel_base, kernel_size, 0x4000, 0x2000, tt2, 0x400000, 0x1000);

	// map stack

	const uintptr_t task1_stack_btm = vmm_allocate_memory(
		task1_dir,
		VMM_PAGE_SIZE * 2,
		PAGING_PTE_FLAG_PRESENT | PAGING_PTE_FLAG_READ_WRITE | PAGING_PDE_FLAG_USER_SUPERVISOR,
		0
	);

	const uintptr_t task2_stack_btm = vmm_allocate_memory(
		task2_dir,
		VMM_PAGE_SIZE * 2,
		PAGING_PTE_FLAG_PRESENT | PAGING_PTE_FLAG_READ_WRITE | PAGING_PDE_FLAG_USER_SUPERVISOR,
		0
	);

	if (task1_stack_btm == UINTPTR_MAX) {
		tty_prints_negative("Error: failed to allocate stack for task1!\n");
		panic_halt();
	}

	if (task2_stack_btm == UINTPTR_MAX) {
		tty_prints_negative("Error: failed to allocate stack for task2!\n");
		panic_halt();
	}

	const uintptr_t task1_stack_top = task1_stack_btm + VMM_PAGE_SIZE * 2;
	const uintptr_t task2_stack_top = task2_stack_btm + VMM_PAGE_SIZE * 2;

	scheduler_task_def_regs_t task1_def_regs = SCHEDULER_STATIC_TASK_DEF_REGS(
		(uint32_t)task1_dir, 0x23, 0x23, task1_stack_top, 0x400000, 0x1b, 0x202
	);

	scheduler_task_def_regs_t task2_def_regs = SCHEDULER_STATIC_TASK_DEF_REGS(
		(uint32_t)task2_dir, 0x23, 0x23, task2_stack_top, 0x400000, 0x1b, 0x202
	);

	scheduler_task_t t1;
	status = scheduler_create_task(
		&task1_def_regs,
		SCHEDULER_TASK_STATE_READY,
		SCHEDULER_TASK_FLAG_NO_AUTOREMOVE,
		&t1
	);
	if (status != STATUS_OK) {
		tty_printf("\x1b[91mError: failed to create task(1) (status: %?)!\n", status);
		panic_halt();
	}
	
	scheduler_task_t t2;
	status = scheduler_create_task(
		&task2_def_regs,
		SCHEDULER_TASK_STATE_READY,
		SCHEDULER_TASK_FLAG_NO_AUTOREMOVE,
		&t2
	);
	if (status != STATUS_OK) {
		tty_printf("\x1b[91mError: failed to create task(2) (status: %?)!\n", status);
		panic_halt();
	}

	status = scheduler_add_task(&t1);
	if (status != STATUS_OK) {
		tty_printf("\x1b[91mError: failed to add task(1) to queue (status: %?)!\n", status);
		panic_halt();
	}

	status = scheduler_add_task(&t2);
	if (status != STATUS_OK) {
		tty_printf("\x1b[91mError: failed to add task(2) to queue (status: %?)!\n", status);
		panic_halt();
	}

	scheduler_enable_task_switching();
	
	tty_prints_positive("3 seconds...\n");
	virt_timer_delay(1000);
	tty_prints_neutral("2 seconds...\n");
	virt_timer_delay(1000);
	tty_prints_negative("1 seconds...\n");
	virt_timer_delay(1000);
	tty_prints_negative("Reached EOF.\n");
	panic_halt();
}

gdt32_t ALIGNED(16) GDT[6];
gdtr32_t ALIGNED(16) GDTR;

paging_pde_t ALIGNED(0x1000) PDE[PAGING_NUM_DIRECTORY_ENTRIES] = { 0 };

tss_t ALIGNED(0x08) TSS;
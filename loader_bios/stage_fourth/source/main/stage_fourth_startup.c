#include <main/stage_fourth_startup.h>

void stage_fourth_startup(boot_info_t* bootloader_info) {
	BOOT_INFO = *bootloader_info;
	gdtr_load(&GDTR);

	exceptions_init();
	irqs_init();
	idt32_init();

	gfx_init(&BOOT_INFO.video_mode);
	tty_init(80, 25, 2, 2, GFX_UNPACK_COLOR(GFX_COLOR_LIGHT_GRAY), 0x18, 0x18, 0x18);

	boot_info_get_features(&BOOT_INFO);
	if (!BOOT_INFO.cpuid_present) {
		// FIXME: not implemented yet...
		tty_prints_negative("Error: machine without CPUID is not supported");
		panic_halt();
		return;
	}
	else if (!BOOT_INFO.fpu_present) {
		// FIXME: not implemented yet...
		tty_prints_negative("Error: machine without x87 FPU is not supported");
		panic_halt();
		return;
	}

	const size_t w = BOOT_INFO.video_mode.width;
	const size_t h = BOOT_INFO.video_mode.height;
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

	tty_printf("Boot drive:\t\t\t\t\x1b[94m%#x\x1b[0m\n", BOOT_INFO.boot_drive);

	const e820_reg_t RESERVED_REGS[] = {
		{	// IVT, BDA
			0x0000000000000000,
			0x0000000000000500,
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
			(uint64_t)(uintptr_t)&__PTR_BASE__,
			(uint64_t)((uintptr_t)&__PTR_END__ - (uintptr_t)&__PTR_BASE__),
			E820_REG_TYPE_RESERVED
		},
		{	// Framebuffer
			(uint64_t)(uintptr_t)GFX_VIDEO_MODE.framebuffer,
			(uint64_t)(GFX_VIDEO_MODE.height * ((GFX_VIDEO_MODE.depth + 7) / 8) * GFX_VIDEO_MODE.pitch),
			E820_REG_TYPE_RESERVED
		}
	};
	
	BOOT_INFO.memory_map_length = pmm_init(
		BOOT_INFO.memory_map,
		BOOT_INFO.memory_map_length,
		RESERVED_REGS,
		sizeof(RESERVED_REGS) / sizeof(RESERVED_REGS[0])
	);

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
	if (BOOT_INFO.vga_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nVBE:\t\t\t\t\t");
	if (BOOT_INFO.vbe_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\ni8042 controller:\t\t");
	if (BOOT_INFO.i8042_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nCPUID:\t\t\t\t\t");
	if (BOOT_INFO.cpuid_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nFPU:\t\t\t\t\t");
	if (BOOT_INFO.fpu_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nSSE version:\t\t\t");
	if (!BOOT_INFO.sse_version) tty_prints_neutral("[NONE]");
	else {
		if (BOOT_INFO.sse_version < 0x10) tty_printf("\x1b[92m%u\x1b[0m", BOOT_INFO.sse_version);
		else {
			if (BOOT_INFO.sse_version == 0x41) tty_printf("\x1b[92m4.1\x1b[0m");
			else if (BOOT_INFO.sse_version == 0x42) tty_printf("\x1b[92m4.2\x1b[0m");
			else tty_printf("\x1b[92m4.2+\x1b[0m");
		}
	}
	
	tty_prints("\nAVX:\t\t\t\t\t");
	if (BOOT_INFO.avx_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nOSXSAVE:\t\t\t\t");
	if (BOOT_INFO.osxsave_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nAPIC:\t\t\t\t\t");
	if (BOOT_INFO.apic_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nMSR:\t\t\t\t\t");
	if (BOOT_INFO.msr_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_printf(
		"\nVideo:\t\t\t\t\tmode=\x1b[96m%xh\x1b[0m (\x1b[96m%u\x1b[0mx\x1b[96m%u\x1b[0m \x1b[94m%ubpp\x1b[0m)\n",
		BOOT_INFO.video_mode.number,
		BOOT_INFO.video_mode.width,
		BOOT_INFO.video_mode.height,
		BOOT_INFO.video_mode.depth
	);

	status_t status = boot_info_parse_acpi_tables(&BOOT_INFO);
	if (status != STATUS_OK) {
		if (status == STATUS_NOT_FOUND) tty_prints_negative("Error: unable to find RSDP");
		else if (status == STATUS_INVALID_HEADER) tty_prints_negative("Error: invalid RSDT header");
		else if (status == STATUS_UNREACHABLE) tty_prints_negative("Error: RSDT unreachable");
		else if (status == STATUS_NO_MEMORY) tty_prints_negative("Error: not enough memory");
		panic_halt();
	}

	tty_printf("RSDP:\t\t\t\t\t\x1b[96m%#010x\x1b[0m\n", BOOT_INFO.acpi_rsdp_address);
	tty_printf("RSDT:\t\t\t\t\t\x1b[96m%#010x\x1b[0m\n", BOOT_INFO.acpi_rsdt_address);
	tty_printf("FADT:\t\t\t\t\t\x1b[96m%#010x\x1b[0m\n", BOOT_INFO.acpi_fadt_address);
	tty_printf("MADT:\t\t\t\t\t\x1b[96m%#010x\x1b[0m\n", BOOT_INFO.acpi_madt_address);

	tty_prints("Interrupt Controller:\t");
	if (BOOT_INFO.apic_present) {
		tty_prints_positive("APIC");
		pic_mask_all_irqs();
		lapic_init();

		tty_puts("\nLAPICs:");
		for (size_t i = 0; i < BOOT_INFO.num_lapics; i++) {
			tty_printf(
				"%u) Processor ID=\x1b[96m%#04x\x1b[0m, APIC ID=\x1b[96m%#04x\x1b[0m, BSP=\x1b[96m%u\x1b[0m\n",
				i + 1,
				BOOT_INFO.lapics[i].acpi_processor_id,
				BOOT_INFO.lapics[i].apic_id,
				BOOT_INFO.lapics[i].bsp
			);
		}

		tty_puts("I/O APICs:");
		for (size_t i = 0; i < BOOT_INFO.num_ioapics; i++) {
			tty_printf(
				"%u) I/O APIC ID=\x1b[96m%#04x\x1b[0m, Base=\x1b[96m%#010x\x1b[0m, GSIB=\x1b[96m%#010x\x1b[0m\n",
				i + 1,
				BOOT_INFO.ioapics[i].ioapic_id,
				BOOT_INFO.ioapics[i].ioapic_base,
				BOOT_INFO.ioapics[i].ioapic_gsib
			);

			if (
				BOOT_INFO.ioapics[i].ioapic_gsib <= 0 &&
				0 < BOOT_INFO.ioapics[i].ioapic_gsib + 24
			) ioapic_init(BOOT_INFO.ioapics[i].ioapic_base);
		}

		tty_puts("I/O APIC Interrupt Source Overrides:");
		for (size_t i = 0; i < BOOT_INFO.num_ioapic_isos; i++) {
			tty_printf(
				"%u) Bus=\x1b[96m%xh\x1b[0m, IRQ=\x1b[96m%02xh\x1b[0m, GSI=\x1b[96m%#010x\x1b[0m\n",
				i + 1,
				BOOT_INFO.ioapic_isos[i].bus,
				BOOT_INFO.ioapic_isos[i].irq,
				BOOT_INFO.ioapic_isos[i].gsi
			);

			if (i >= NUM_IRQS) continue;
			
			boot_info_ioapic_iso_t* ioapiciso = &BOOT_INFO.ioapic_isos[i];
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
		virt_int_ctrl_eoi = lapic_eoi;
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
	if (BOOT_INFO.apic_present) {
		tty_prints_positive("LAPIC, PIT\n");

		irq_info_t pit_irq_info;
		irq_get_info(PIT_IRQ, &pit_irq_info);
		irq_set(PIT_IRQ, virt_timer_irq_handler);
		irq_set(LAPIC_TIMER_VECTOR - 32, virt_timer_irq_handler);
		virt_int_ctrl_unmask_irq(pit_irq_info.irq_remapped);
		lapic_timer_init(LAPIC_TIMER_VECTOR);
		virt_int_ctrl_mask_irq(pit_irq_info.irq_remapped);
		irq_set(PIT_IRQ, NULL);
	}
	else {
		tty_prints_positive("PIT\n");
		
		irq_info_t pit_irq_info;
		irq_get_info(PIT_IRQ, &pit_irq_info);
		irq_set(PIT_IRQ, virt_timer_irq_handler);
		
		pit_init(PIT_COMMAND_SQUARE_WAVE, PIT_COMMAND_CHNL0, 10);
		virt_int_ctrl_unmask_irq(pit_irq_info.irq_remapped);
	}

	tty_prints("Paging:\t\t\t\t\t");
	// Identity mapping (1:1)
	memset(&PDE[0], 0, sizeof(PDE));
	paging_map_pages(PDE, 0, 0, 0x100000, PAGING_PTE_FLAG_PRESENT | PAGING_PTE_FLAG_READ_WRITE);
	paging_load_directory(PDE);
	paging_enable();

	tty_prints_positive("[ENABLED]\n");

	tty_prints_positive("3 seconds...\n");
	virt_timer_sleep(1000);
	tty_prints_neutral("2 seconds...\n");
	virt_timer_sleep(1000);
	tty_prints_negative("1 seconds...\n");
	virt_timer_sleep(1000);
	tty_prints_negative("Reached EOF.\n");
	
	panic_halt();
}

boot_info_t BOOT_INFO = { 0 };

gdt32_t ALIGNED(16) GDT[3] = {
	GDT32_STATIC(0, 0, 0, 0),
	GDT32_STATIC(
		0xfffff,
		0,
		GDT_ACCESS_READABLE_WRITEABLE | GDT_ACCESS_EXECUTABLE | GDT_ACCESS_NOT_SYSTEM | GDT_ACCESS_PRESENT,
		GDT_FLAG_SIZE | GDT_FLAG_GRANULARITY
	),
	GDT32_STATIC(
		0xfffff,
		0,
		GDT_ACCESS_READABLE_WRITEABLE | GDT_ACCESS_NOT_SYSTEM | GDT_ACCESS_PRESENT,
		GDT_FLAG_SIZE | GDT_FLAG_GRANULARITY
	)
};

gdtr32_t ALIGNED(16) GDTR = GDTR_STATIC(
	sizeof(GDT),
	(uintptr_t)&GDT[0]
);

paging_pde_t ALIGNED(0x1000) PDE[PAGING_NUM_DIRECTORY_ENTRIES] = { 0 };
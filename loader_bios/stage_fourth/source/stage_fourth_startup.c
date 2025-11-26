#include <boot/boot_info.h>
#include <asm.h>
#include <cpuid486/cpuid486.h>
#include <gfx/gfx.h>
#include <tty/tty.h>
#include <pmm/pmm.h>
#include <fpu/fpu.h>
#include <paging/paging.h>
#include <acpi/acpi.h>
#include <gdt/gdt.h>

extern uint32_t __PTR_BASE__[];
extern uint32_t __PTR_END__[];

extern gfx_video_mode_t GFX_VIDEO_MODE;
static boot_info_t BOOT_INFO;
static paging_pde_t ALIGNED(0x1000) PDE[PAGING_NUM_DIRECTORY_ENTRIES];

static gdt32_t ALIGNED(16) GDT_FOURTH_STAGE[] = {
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

static gdt_descriptor32_t ALIGNED(16) GDT_DESCRIPTOR_FOURTH_STAGE = GDT_DESCRIPTOR_STATIC(
	sizeof(GDT_FOURTH_STAGE),
	GDT_FOURTH_STAGE
);

void stage_fourth_startup(boot_info_t* bootloader_info) {
	BOOT_INFO = *bootloader_info;
	gdt_reload(&GDT_DESCRIPTOR_FOURTH_STAGE);

	gfx_init(&BOOT_INFO.video_mode);
	tty_init(80, 25, 2, 2, GFX_UNPACK_COLOR(GFX_COLOR_LIGHT_GRAY), 0x18, 0x18, 0x18);

	bool cpuid_prsnt = cpuid486_present();
	bool fpu_prsnt = false;
	bool avx_prsnt = false;
	size_t sse_version = 0;
	if (cpuid_prsnt) {
		BOOT_INFO.cpuid_present = true;

		uint32_t ecx;
		uint32_t edx;
		cpuid486_get_features(&ecx, &edx);
		
		fpu_prsnt = (edx & CPUID486_EDX_FEATURE_FPU) != 0;
		if (ecx & CPUID486_ECX_FEATURE_SSE4_2) sse_version = 0x42;
		else if (ecx & CPUID486_ECX_FEATURE_SSE4_1) sse_version = 0x41;
		else if (ecx & CPUID486_ECX_FEATURE_SSE3) sse_version = 0x03;
		else if (edx & CPUID486_EDX_FEATURE_SSE2) sse_version = 0x02;
		else if (edx & CPUID486_EDX_FEATURE_SSE) sse_version = 0x01;

		if (fpu_prsnt) fpu_init(sse_version != 0, sse_version != 0, ecx & CPUID486_ECX_FEATURE_OSXSAVE);

		cpuid486_get_features(&ecx, &edx);
		if (fpu_prsnt && (ecx & CPUID486_ECX_FEATURE_OSXSAVE)) {
			uint32_t low;
			uint32_t high;
			xgetbv(0, &low, &high);
			low |= 0b111;			// x87 FPU + SSE + AVX
			xsetbv(0, low, high);
		}
		
		cpuid486_get_features(&ecx, &edx);
		if (ecx & CPUID486_ECX_FEATURE_AVX) {
			avx_prsnt = true;
			if (sse_version < 0x42) sse_version = 0x42;
		}
	}
	else {
		BOOT_INFO.cpuid_present = false;
		// FIXME: not implemented yet...
		tty_prints_negative("Error: machine without CPUID is not supported!");
		panic_halt();
	}

	BOOT_INFO.fpu_present = fpu_prsnt;
	BOOT_INFO.sse_version = sse_version;
	BOOT_INFO.avx_present = avx_prsnt;
	if (fpu_prsnt) {
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
	}
	else {
		// FIXME: not implemented yet...
		tty_prints_negative("Error: machine without x87 FPU is not supported!");
		panic_halt();
	}

	gfx_fill_rectangle(0, 0, GFX_VIDEO_MODE.width, GFX_VIDEO_MODE.height, 0x18, 0x18, 0x18);
	tty_puts_color(
		"Welcome to LZST bootloader!",
		0xff, 0x7f, 0,
		0x18, 0x18, 0x18
	);

	tty_printf("Boot drive:\t\t\t\x1b[94m%#x\x1b[0m\n", BOOT_INFO.boot_drive);

	tty_prints("VGA:\t\t\t\t");
	if (BOOT_INFO.vga_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nVBE:\t\t\t\t");
	if (BOOT_INFO.vbe_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\ni8042 controller:\t");
	if (BOOT_INFO.i8042_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nCPUID:\t\t\t\t");
	if (BOOT_INFO.cpuid_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nFPU:\t\t\t\t");
	if (BOOT_INFO.fpu_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nSSE version:\t\t");
	if (!BOOT_INFO.sse_version) tty_prints_neutral("[NONE]");
	else {
		if (BOOT_INFO.sse_version < 0x10) tty_printf("\x1b[92m%u\x1b[0m", BOOT_INFO.sse_version);
		else {
			if (BOOT_INFO.sse_version == 0x41) tty_printf("\x1b[92m4.1\x1b[0m");
			else if (BOOT_INFO.sse_version == 0x42) tty_printf("\x1b[92m4.2\x1b[0m");
			else tty_printf("\x1b[92m4.2+\x1b[0m");
		}
	}
	
	tty_prints("\nAVX:\t\t\t\t");
	if (BOOT_INFO.avx_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_printf(
		"\nVideo:\t\t\t\tmode=\x1b[96m%xh\x1b[0m (\x1b[96m%u\x1b[0mx\x1b[96m%u\x1b[0m \x1b[94m%ubpp\x1b[0m)\n",
		BOOT_INFO.video_mode.number,
		BOOT_INFO.video_mode.width,
		BOOT_INFO.video_mode.height,
		BOOT_INFO.video_mode.depth
	);

	uint64_t acpi_rsdp_xsdp_address = (uint64_t)(uintptr_t)acpi_find_rsdp_xsdp();
	if (!acpi_rsdp_xsdp_address) {
		tty_prints("RSDP/XSDP: unable to find RSDP table");

		panic_halt();
	}

	acpi_rsdp_t* acpi_rsdp = (acpi_rsdp_t*)(uintptr_t)acpi_rsdp_xsdp_address;
	acpi_xsdp_t* acpi_xsdp = (acpi_xsdp_t*)(uintptr_t)acpi_rsdp_xsdp_address;
	if (acpi_rsdp->revision >= 2) {
		acpi_xsdt_t* acpi_xsdt = (acpi_xsdt_t*)(uintptr_t)acpi_xsdp->xsdt_address;
		if (!acpi_validate_sdt_header(&acpi_xsdt->header, ACPI_XSDT_SIGNATURE)) {
			tty_prints_negative("Error: invalid XSDT");
			panic_halt();
		}

		BOOT_INFO.acpi_xsdp_address = acpi_rsdp_xsdp_address;
		BOOT_INFO.acpi_xsdp_version = acpi_xsdp->revision;
		BOOT_INFO.acpi_xsdt_address = acpi_xsdp->rsdt_address;
		BOOT_INFO.acpi_fadt_address = (uint64_t)(uintptr_t)acpi_find_sdt64(acpi_xsdt, ACPI_FADT_SIGNATURE);
		BOOT_INFO.acpi_madt_address = (uint64_t)(uintptr_t)acpi_find_sdt64(acpi_xsdt, ACPI_MADT_SIGNATURE);

		tty_printf(
			"XSDP:\t\t\t\t\x1b[96m%#010x%08x\x1b[0m\n",
			(uint32_t)(BOOT_INFO.acpi_xsdp_address >> 32),
			(uint32_t)(BOOT_INFO.acpi_xsdp_address & 0xffffffff)
		);

		tty_printf(
			"XSDT:\t\t\t\t\x1b[96m%#010x%08x\x1b[0m\n",
			(uint32_t)(BOOT_INFO.acpi_xsdt_address >> 32),
			(uint32_t)(BOOT_INFO.acpi_xsdt_address & 0xffffffff)
		);
	}
	else {
		acpi_rsdt_t* acpi_rsdt = (acpi_rsdt_t*)acpi_rsdp->rsdt_address;
		if (!acpi_validate_sdt_header(&acpi_rsdt->header, ACPI_RSDT_SIGNATURE)) {
			tty_prints_negative("Error: invalid RSDT");
			panic_halt();
		}

		BOOT_INFO.acpi_rsdp_address = (uintptr_t)acpi_rsdp_xsdp_address;
		BOOT_INFO.acpi_rsdp_version = acpi_rsdp->revision;
		BOOT_INFO.acpi_rsdt_address = (uintptr_t)acpi_rsdp->rsdt_address;
		BOOT_INFO.acpi_fadt_address = (uint64_t)(uintptr_t)acpi_find_sdt32(acpi_rsdt, ACPI_FADT_SIGNATURE);
		BOOT_INFO.acpi_madt_address = (uint64_t)(uintptr_t)acpi_find_sdt32(acpi_rsdt, ACPI_MADT_SIGNATURE);

		tty_printf(
			"RSDP:\t\t\t\t\x1b[96m%#08x\x1b[0m\n",
			BOOT_INFO.acpi_rsdp_address
		);

		tty_printf(
			"RSDT:\t\t\t\t\x1b[96m%#08x\x1b[0m\n",
			BOOT_INFO.acpi_rsdt_address
		);
	}

	tty_printf(
		"FADT:\t\t\t\t\x1b[96m%#010x%08x\x1b[0m\n",
		(uint32_t)(BOOT_INFO.acpi_fadt_address >> 32),
		(uint32_t)(BOOT_INFO.acpi_fadt_address & 0xffffffff)
	);

	tty_printf(
		"MADT:\t\t\t\t\x1b[96m%#010x%08x\x1b[0m\n",
		(uint32_t)(BOOT_INFO.acpi_madt_address >> 32),
		(uint32_t)(BOOT_INFO.acpi_madt_address & 0xffffffff)
	);

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

	// Identity mapping (1:1)
	memset(&PDE[0], 0, sizeof(PDE));
	paging_map_pages(PDE, 0, 0, 0x100000, PAGING_PTE_FLAG_PRESENT | PAGING_PTE_FLAG_READ_WRITE);
	paging_load_directory(PDE);
	paging_enable();

	tty_puts("Paging enabled");
	
	panic_halt();
}
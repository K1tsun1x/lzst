#include <boot/boot_info.h>
#include <asm.h>
#include <cpuid486/cpuid486.h>
#include <gfx/gfx.h>
#include <tty/tty.h>
#include <pmm/pmm.h>
#include <fpu/fpu.h>

extern uint32_t __PTR_BASE__[];
extern uint32_t __PTR_END__[];

extern gfx_video_mode_t GFX_VIDEO_MODE;

static boot_info_t BOOT_INFO;

void stage_fourth_startup(boot_info_t* bootloader_info) {
	BOOT_INFO = *bootloader_info;
	gfx_init(&BOOT_INFO.video_mode);
	tty_init(80, 25, 2, 2);

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

		tty_init(num_chars_per_line, num_lines, 2, 2);
	}
	else {
		// FIXME: not implemented yet...
		tty_prints_negative("Error: machine without x87 FPU is not supported!");
		panic_halt();
	}

	const gfx_color_t tty_bkg_color = GFX_PACK_COLOR(0x18, 0x18, 0x18);
	const gfx_color_t tty_frg_color = GFX_COLOR_LIGHT_GRAY;
	gfx_fill_rectangle(0, 0, GFX_VIDEO_MODE.width, GFX_VIDEO_MODE.height, GFX_UNPACK_COLOR(tty_bkg_color));
	tty_puts("Welcome to LZST bootloader!", 0xff, 0x7f, 0, GFX_UNPACK_COLOR(tty_bkg_color), true);

	tty_printf(
		GFX_UNPACK_COLOR(tty_frg_color),
		GFX_UNPACK_COLOR(tty_bkg_color),
		false,
		"Boot drive:\t\t\t\x1b[94m%#x\x1b[0m\n", BOOT_INFO.boot_drive
	);

	tty_prints("VGA:\t\t\t\t", GFX_UNPACK_COLOR(tty_frg_color), GFX_UNPACK_COLOR(tty_bkg_color), true);
	if (BOOT_INFO.vga_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nVBE:\t\t\t\t", GFX_UNPACK_COLOR(tty_frg_color), GFX_UNPACK_COLOR(tty_bkg_color), true);
	if (BOOT_INFO.vbe_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\ni8042 controller:\t", GFX_UNPACK_COLOR(tty_frg_color), GFX_UNPACK_COLOR(tty_bkg_color), true);
	if (BOOT_INFO.i8042_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nCPUID:\t\t\t\t", GFX_UNPACK_COLOR(tty_frg_color), GFX_UNPACK_COLOR(tty_bkg_color), true);
	if (BOOT_INFO.cpuid_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nFPU:\t\t\t\t", GFX_UNPACK_COLOR(tty_frg_color), GFX_UNPACK_COLOR(tty_bkg_color), true);
	if (BOOT_INFO.fpu_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_prints("\nSSE version:\t\t", GFX_UNPACK_COLOR(tty_frg_color), GFX_UNPACK_COLOR(tty_bkg_color), true);
	if (!BOOT_INFO.sse_version) tty_prints_neutral("[NONE]");
	else {
		if (BOOT_INFO.sse_version < 0x10) tty_printf(
			GFX_UNPACK_COLOR(tty_frg_color),
			GFX_UNPACK_COLOR(tty_bkg_color),
			false,
			"\x1b[92m%u\x1b[0m", BOOT_INFO.sse_version
		);
		else {
			if (BOOT_INFO.sse_version == 0x41) tty_printf(
				GFX_UNPACK_COLOR(tty_frg_color),
				GFX_UNPACK_COLOR(tty_bkg_color),
				false,
				"\x1b[92m4.1\x1b[0m"
			);
			else if (BOOT_INFO.sse_version == 0x42) tty_printf(
				GFX_UNPACK_COLOR(tty_frg_color),
				GFX_UNPACK_COLOR(tty_bkg_color),
				false,
				"\x1b[92m4.2\x1b[0m"
			);
			else tty_printf(
				GFX_UNPACK_COLOR(tty_frg_color),
				GFX_UNPACK_COLOR(tty_bkg_color),
				false,
				"\x1b[92m4.2+\x1b[0m"
			);
		}
	}
	
	tty_prints("\nAVX:\t\t\t\t", GFX_UNPACK_COLOR(tty_frg_color), GFX_UNPACK_COLOR(tty_bkg_color), true);
	if (BOOT_INFO.avx_present) tty_prints_positive("[PRESENT]");
	else tty_prints_negative("[NOT PRESENT]");
	
	tty_printf(
		GFX_UNPACK_COLOR(tty_frg_color),
		GFX_UNPACK_COLOR(tty_bkg_color),
		false,
		"\nVideo:\t\t\t\tmode=\x1b[96m%xh\x1b[0m (\x1b[96m%u\x1b[0mx\x1b[96m%u\x1b[0m \x1b[94m%ubpp\x1b[0m)\n",
		BOOT_INFO.video_mode.number,
		BOOT_INFO.video_mode.width,
		BOOT_INFO.video_mode.height,
		BOOT_INFO.video_mode.depth
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

	tty_puts("Normalized usable memory map:", GFX_UNPACK_COLOR(tty_frg_color), GFX_UNPACK_COLOR(tty_bkg_color), true);
	pmm_reg_t* first_pmm_reg = (pmm_reg_t*)PMM_FIRST_REGION_BASE_ADDRESS;
	do {
		tty_printf(
			GFX_UNPACK_COLOR(tty_frg_color),
			GFX_UNPACK_COLOR(tty_bkg_color),
			false,
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

	tty_puts("Allocate A: ", GFX_UNPACK_COLOR(tty_frg_color), GFX_UNPACK_COLOR(tty_bkg_color), true);
	void* a = pmm_allocate_memory(0x1234, 0);
	tty_printf(
		GFX_UNPACK_COLOR(tty_frg_color),
		GFX_UNPACK_COLOR(tty_bkg_color),
		false,
		"Base: \x1b[96m%#010x\x1b[0m\n",
		(uintptr_t)a
	);
	memset(a, 0xff, 0x1234);

	tty_puts("Allocate B: ", GFX_UNPACK_COLOR(tty_frg_color), GFX_UNPACK_COLOR(tty_bkg_color), true);
	void* b = pmm_allocate_memory(0x5678, 0);
	tty_printf(
		GFX_UNPACK_COLOR(tty_frg_color),
		GFX_UNPACK_COLOR(tty_bkg_color),
		false,
		"Base: \x1b[96m%#010x\x1b[0m\n",
		(uintptr_t)b
	);
	memset(b, 0xcc, 0x5678);

	tty_puts("Free A: ", GFX_UNPACK_COLOR(tty_frg_color), GFX_UNPACK_COLOR(tty_bkg_color), true);
	tty_printf(
		GFX_UNPACK_COLOR(tty_frg_color),
		GFX_UNPACK_COLOR(tty_bkg_color),
		false,
		"Result: \x1b[96m%u\x1b[0m\n",
		pmm_free_memory(a)
	);

	tty_puts("Allocate C: ", GFX_UNPACK_COLOR(tty_frg_color), GFX_UNPACK_COLOR(tty_bkg_color), true);
	void* c = pmm_allocate_memory(0x123, 0);
	tty_printf(
		GFX_UNPACK_COLOR(tty_frg_color),
		GFX_UNPACK_COLOR(tty_bkg_color),
		false,
		"Base: \x1b[96m%#010x\x1b[0m\n",
		(uintptr_t)c
	);
	memset(c, 0xdd, 0x123);

	tty_puts("Reallocate B: ", GFX_UNPACK_COLOR(tty_frg_color), GFX_UNPACK_COLOR(tty_bkg_color), true);
	b = pmm_reallocate_memory(b, 0x200000, 0);
	memset(b, 0xaa, 0x200000);
	tty_printf(
		GFX_UNPACK_COLOR(tty_frg_color),
		GFX_UNPACK_COLOR(tty_bkg_color),
		false,
		"Base: \x1b[96m%#010x\x1b[0m\n",
		(uintptr_t)b
	);
	
	panic_halt();
}
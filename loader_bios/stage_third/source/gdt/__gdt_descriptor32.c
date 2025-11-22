#include <gdt.h>

extern const gdt32_t __GDT32[3];
const gdt_descriptor32_t ALIGNED(16) __GDT_DESCRIPTOR32 = GDT_DESCRIPTOR_STATIC(
	sizeof(__GDT32),
	(uint32_t)(&__GDT32[0])
);
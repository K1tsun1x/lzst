#include <gdt.h>

extern const gdt32_t __GDT16[3];
const gdt_descriptor32_t ALIGNED(16) __GDT_DESCRIPTOR16 = GDT_DESCRIPTOR_STATIC(
	sizeof(__GDT16),
	(uint32_t)(&__GDT16[0])
);
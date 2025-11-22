#include <min_stdio.h>

uint16_t __min_stdio_offset = 0;

EXTERN_C void LOADERCALL __min_stdio_write_word(uint16_t offset, uint16_t value);

void min_stdio_init(void) {
	uint16_t tmp_offset = 0;
	const uint16_t end_offset = TTY_SIZE;
	for (; tmp_offset < end_offset; tmp_offset += 2) __min_stdio_write_word(
		tmp_offset,
		(uint16_t)((COLOR_LIGHT_GRAY << 8) | ' ')
	);

	__min_stdio_offset = 0;
}
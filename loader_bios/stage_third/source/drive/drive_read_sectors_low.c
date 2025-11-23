#include <drive.h>

EXTERN_C bool LOADERCALL __drive_read_sector_block(
	uint8_t drive,
	uint16_t count,
	uint16_t buffer_off,
	uint16_t buffer_seg,
	uint32_t lba_low,
	uint32_t lba_high
);

bool drive_read_sectors_low(
	uint8_t drive,
	uint16_t buffer_off, uint16_t buffer_seg,
	uint64_t lba,
	uint32_t num_sectors
) {
	uint32_t num_blocks = num_sectors / DRIVE_MAX_SECTORS_PER_READ_OPERATION;
	num_sectors -= num_blocks * DRIVE_MAX_SECTORS_PER_READ_OPERATION;

	const uint32_t sectors_block_size = DRIVE_SECTOR_SIZE * (uint32_t)DRIVE_MAX_SECTORS_PER_READ_OPERATION;
	const uint32_t last_dst_block = 0x100000 - sectors_block_size;
	for (; num_blocks; --num_blocks) {
		if (!__drive_read_sector_block(
			drive,
			DRIVE_MAX_SECTORS_PER_READ_OPERATION,
			buffer_off, buffer_seg,
			(uint32_t)(lba & 0xffffffff),
			(uint32_t)(lba >> 32)
		)) return false;

		uint32_t dst = ((uint32_t)(buffer_seg) << 4) + (uint32_t)buffer_off;
		if (dst >= last_dst_block) break;

		dst += sectors_block_size;
		buffer_seg = dst >> 4;
		buffer_off = dst & 0x0f;

		lba += DRIVE_MAX_SECTORS_PER_READ_OPERATION;
	}

	if (num_blocks) return false;

	if (num_sectors) return __drive_read_sector_block(
		drive,
		num_sectors & DRIVE_SECTOR_MASK,
		buffer_off, buffer_seg,
		(uint32_t)lba & 0xffffffff,
		(uint32_t)(lba >> 32)
	);

	return true;
}
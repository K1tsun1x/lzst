#include <drive.h>

extern uint8_t __DRIVE;
extern uint8_t __SECTORS_PER_TRACK;
extern uint8_t __LAST_HEAD_INDEX;

EXTERN_C bool LOADERCALL __drive_read_sector(uint8_t al, uint16_t cx, uint16_t dx, uint16_t es, uint16_t bx);

bool drive_read_sectors_low(uint32_t lba, uint16_t buffer_seg, uint16_t buffer_off, uint32_t num_sectors) {
	uint8_t head;
	uint8_t sector;
	uint16_t cylinder;
	if (!drive_lba_to_chs(lba, &cylinder, &head, &sector)) return false;

	uint32_t num_blocks = num_sectors / __SECTORS_PER_TRACK;
	num_sectors -= num_blocks * __SECTORS_PER_TRACK;

	const uint32_t sectors_block_size = DRIVE_SECTOR_SIZE * (uint32_t)__SECTORS_PER_TRACK;
	const uint32_t last_dst_block = 0x100000 - sectors_block_size;
	const uint8_t last_head = __LAST_HEAD_INDEX;
	for (; num_blocks; --num_blocks) {
		if (!__drive_read_sector(
				__SECTORS_PER_TRACK,
				CHS_BUILD_CX(cylinder, sector),
				CHS_BUILD_DX(__DRIVE, head),
				buffer_seg,
				buffer_off
			)
		) return false;

		uint32_t dst = ((uint32_t)(buffer_seg) << 4) + (uint32_t)buffer_off;
		if (dst >= last_dst_block) break;

		dst += sectors_block_size;
		buffer_seg = dst >> 4;
		buffer_off = dst & 0x0f;

		++head;
		if (head > last_head) {
			++cylinder;
			head = 0;
		}
	}

	if (num_blocks) return false;

	if (num_sectors) return __drive_read_sector(
		(uint8_t)num_sectors,
		CHS_BUILD_CX(cylinder, sector),
		CHS_BUILD_DX(__DRIVE, head),
		buffer_seg,
		buffer_off
	);

	return true;
}
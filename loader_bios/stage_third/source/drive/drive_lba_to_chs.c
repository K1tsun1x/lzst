#include <drive.h>

extern uint8_t __SECTORS_PER_TRACK;
extern uint8_t __LAST_HEAD_INDEX;

bool drive_lba_to_chs(uint32_t lba, uint16_t* cylinder, uint8_t* head, uint8_t* sector) {
	uint16_t heads = ((uint16_t)__LAST_HEAD_INDEX) + 1;
	uint16_t sectors_per_cylinder = ((uint16_t)__SECTORS_PER_TRACK) * heads;

	uint32_t tmp = lba % (uint32_t)sectors_per_cylinder;
	uint32_t ccylinder = lba / (uint32_t)sectors_per_cylinder;
	uint32_t chead = tmp / __SECTORS_PER_TRACK;
	uint32_t csector = (tmp % __SECTORS_PER_TRACK) + 1;
	
	if (ccylinder > 0x3ff || !csector || csector > DRIVE_MAX_SECTORS_PER_READ_OPERATION || chead > 0xff) return false;

	if (cylinder) *cylinder = (uint16_t)ccylinder;
	if (head) *head = (uint8_t)chead;
	if (sector) *sector = (uint8_t)csector;
	return true;
}
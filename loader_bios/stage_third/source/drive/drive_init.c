#include <drive.h>

extern uint8_t __DRIVE;
extern uint8_t __SECTORS_PER_TRACK;
extern uint8_t __LAST_HEAD_INDEX;

EXTERN_C bool LOADERCALL __drive_read_params(uint8_t drive, uint8_t* dh, uint16_t* cx);

bool drive_init(uint8_t drive) {
	uint8_t dh;
	uint16_t cx;
	if (!__drive_read_params(drive, &dh, &cx)) return false;

	__DRIVE = drive;
	__SECTORS_PER_TRACK = (uint8_t)(cx & DRIVE_SECTOR_MASK);
	__LAST_HEAD_INDEX = dh;
	return true;
}
#include <drive.h>

extern uint8_t __SECTORS_PER_TRACK;

uint8_t drive_get_sectors_per_track(void) {
	return __SECTORS_PER_TRACK;
}
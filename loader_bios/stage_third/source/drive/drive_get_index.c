#include <drive.h>

extern uint8_t __DRIVE;

uint8_t drive_get_index(void) {
	return __DRIVE;
}
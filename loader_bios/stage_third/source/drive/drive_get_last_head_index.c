#include <drive.h>

extern uint8_t __LAST_HEAD_INDEX;

uint8_t drive_get_last_head_index(void) {
	return __LAST_HEAD_INDEX;
}
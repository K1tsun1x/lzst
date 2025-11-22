#include <drive.h>

uint8_t __DRIVE = 0x80;
uint8_t __SECTORS_PER_TRACK = DRIVE_MAX_SECTORS_PER_READ_OPERATION;
uint8_t __LAST_HEAD_INDEX = 0x0f;
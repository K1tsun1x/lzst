#pragma once
#ifndef __DRIVE_H
#define __DRIVE_H

#include "typedefs.h"

#define DRIVE_SECTOR_SIZE						512
#define DRIVE_MAX_SECTORS_PER_READ_OPERATION	0x7f
#define DRIVE_SECTOR_MASK						DRIVE_MAX_SECTORS_PER_READ_OPERATION

bool drive_read_sectors_low(
	uint8_t drive,
	uint16_t buffer_off, uint16_t buffer_seg,
	uint64_t lba,
	uint32_t num_sectors
);

#endif
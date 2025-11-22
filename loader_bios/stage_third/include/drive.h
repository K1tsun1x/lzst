#pragma once
#ifndef __DRIVE_H
#define __DRIVE_H

#include "chs.h"

#define DRIVE_SECTOR_SIZE						512
#define DRIVE_MAX_SECTORS_PER_READ_OPERATION	0x3f
#define DRIVE_SECTOR_MASK						DRIVE_MAX_SECTORS_PER_READ_OPERATION

bool drive_init(uint8_t drive);
uint8_t drive_get_index(void);
uint8_t drive_get_sectors_per_track(void);
uint8_t drive_get_last_head_index(void);
bool drive_lba_to_chs(uint32_t lba, uint16_t* cylinder, uint8_t* head, uint8_t* sector);
bool drive_read_sectors_low(uint32_t lba, uint16_t buffer_seg, uint16_t buffer_off, uint32_t num_sectors);

#endif
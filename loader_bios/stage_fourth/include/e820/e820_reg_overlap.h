#pragma once
#ifndef __E820_REG_OVERLAP_H
#define __E820_REG_OVERLAP_H

#include "e820_reg.h"

typedef enum _e820_reg_overlap_t {
	E820_REG_OVERLAP_NONE =			0,

	/*
		intersection at the beginning
		of the first region
		(i.e. overlaps the beginning)
	*/
	E820_REG_OVERLAP_START =		1,
	
	/*
		intersection at the end
		of the first region
	*/
	E820_REG_OVERLAP_END =			2,
	
	/*
		the first region
		is completely inside the second
	*/
	E820_REG_OVERLAP_INSIDE =		3,
	
	/*
		the first region
		completely covers the second
	*/
	E820_REG_OVERLAP_OUTSIDE =		4
} e820_reg_overlap_t;

e820_reg_overlap_t e820_get_reg_overlap(const e820_reg_t* first, const e820_reg_t* second);

#endif
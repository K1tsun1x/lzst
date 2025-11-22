#pragma once
#ifndef __CHS_H
#define __CHS_H

#include "typedefs.h"

#define CHS_BUILD_CX(cylinder, sector)			( \
	((uint16_t)(cylinder & 0xff) << 8) | \
	((uint16_t)(cylinder >> 2) & 0xc0) | \
	(uint16_t)(sector & 0x3f) \
)

#define CHS_BUILD_DX(drive, head)				( \
	(((uint16_t)head) << 8) | \
	(((uint16_t)drive) & 0xff) \
)

#endif
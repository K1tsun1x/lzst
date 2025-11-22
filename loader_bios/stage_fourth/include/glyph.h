#pragma once
#ifndef __GLYPH_H
#define __GLYPH_H

#include "typedefs.h"

typedef struct _glyph8x8_t {
	char32_t		index;
	uint8_t			data[8];
} glyph8x8_t;

extern const glyph8x8_t GLYPH_UNKNOWN8X8;

#endif
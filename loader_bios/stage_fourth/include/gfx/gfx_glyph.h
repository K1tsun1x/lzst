#pragma once
#ifndef __GFX_GLYPH_H
#define __GFX_GLYPH_H

#include <typedefs.h>

typedef struct _gfx_glyph8x8_t {
	char32_t		index;
	uint8_t			data[8];
} gfx_glyph8x8_t;

#endif
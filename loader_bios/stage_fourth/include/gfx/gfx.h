#pragma once
#ifndef __GFX_H
#define __GFX_H

#include "gfx_color.h"
#include "gfx_draw_pixel.h"
#include "gfx_read_pixel.h"
#include "gfx_copy_rectangle.h"
#include "gfx_fill_rectangle.h"

#include "gfx_draw_glyph.h"
#include "gfx_draw_string.h"

void gfx_init(const gfx_video_mode_t* vm);

#endif
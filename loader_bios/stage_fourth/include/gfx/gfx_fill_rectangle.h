#pragma once
#ifndef __GFX_FILL_RECTANGLE_H
#define __GFX_FILL_RECTANGLE_H

#include "gfx_video_mode.h"
#include "gfx_draw_pixel.h"

void gfx_fill_rectangle(int x, int y, size_t width, size_t height, uint8_t r, uint8_t g, uint8_t b);

#endif
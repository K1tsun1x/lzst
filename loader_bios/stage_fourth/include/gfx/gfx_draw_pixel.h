#pragma once
#ifndef __GFX_DRAW_PIXEL_H
#define __GFX_DRAW_PIXEL_H

#include "gfx_video_mode.h"
#include "gfx_color.h"

typedef void (*pgfx_draw_pixel)(int x, int y, uint8_t r, uint8_t g, uint8_t b);

/**
 * Only for indexed video mode with 8 bits per pixel
 */
void gfx_draw_pixel_i8(int x, int y, uint8_t r, uint8_t g, uint8_t b);

/**
 * Only for non-index video mode with 15 or 16 bits per pixel (RGB)
 */
void gfx_draw_pixel555_565(int x, int y, uint8_t r, uint8_t g, uint8_t b);

/**
 * Only for non-index video mode with 24 bits per pixel (RGB)
 */
void gfx_draw_pixel888(int x, int y, uint8_t r, uint8_t g, uint8_t b);

/**
 * Only for non-index video mode with 32 bits per pixel (ARGB, A - reserved)
 */
void gfx_draw_pixel8888(int x, int y, uint8_t r, uint8_t g, uint8_t b);

/**
 * Needed if there is no suitable gfx_draw_pixel*
 */
void gfx_draw_pixel_stub(int x, int y, uint8_t r, uint8_t g, uint8_t b);

extern pgfx_draw_pixel gfx_draw_pixel;

#endif
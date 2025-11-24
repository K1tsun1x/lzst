#pragma once
#ifndef __GFX_COPY_RECTANGLE_H
#define __GFX_COPY_RECTANGLE_H

#include "gfx_video_mode.h"
#include "gfx_color.h"

typedef void (*pgfx_copy_rectangle)(int src_x, int src_y, int dst_x, int dst_y, size_t width, size_t height);

/**
 * Only for indexed video mode with 8 bits per pixel
 */
void gfx_copy_rectangle_i8(int src_x, int src_y, int dst_x, int dst_y, size_t width, size_t height);

/**
 * Only for non-index video mode with 15 or 16 bits per pixel (RGB)
 */
void gfx_copy_rectangle555_565(int src_x, int src_y, int dst_x, int dst_y, size_t width, size_t height);

/**
 * Only for non-index video mode with 24 bits per pixel (RGB)
 */
void gfx_copy_rectangle888(int src_x, int src_y, int dst_x, int dst_y, size_t width, size_t height);

/**
 * Only for non-index video mode with 32 bits per pixel (ARGB, A - reserved)
 */
void gfx_copy_rectangle8888(int src_x, int src_y, int dst_x, int dst_y, size_t width, size_t height);

/**
 * Needed if there is no suitable gfx_copy_rectangle*
 */
void gfx_copy_rectangle_stub(int src_x, int src_y, int dst_x, int dst_y, size_t width, size_t height);

extern pgfx_copy_rectangle gfx_copy_rectangle;

#endif
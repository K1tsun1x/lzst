#include <gfx.h>

video_mode_t GFX_VIDEO_MODE;
uint8_t* GFX_BUFFER = (uint8_t*)0xa0000;
pgfx_draw_pixel gfx_draw_pixel = NULL;
pgfx_read_pixel gfx_read_pixel = NULL;
pgfx_copy_rectangle gfx_copy_rectangle = NULL;
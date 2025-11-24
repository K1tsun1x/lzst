#include <gfx/gfx.h>

gfx_video_mode_t GFX_VIDEO_MODE;
uint8_t* GFX_BUFFER;
pgfx_draw_pixel gfx_draw_pixel = NULL;
pgfx_read_pixel gfx_read_pixel = NULL;
pgfx_copy_rectangle gfx_copy_rectangle = NULL;

void gfx_init(const gfx_video_mode_t* vm) {
	GFX_VIDEO_MODE = *vm;
	GFX_BUFFER = (uint8_t*)GFX_VIDEO_MODE.framebuffer;

	if (GFX_VIDEO_MODE.depth == 8) {
		gfx_draw_pixel = gfx_draw_pixel_i8;
		gfx_read_pixel = gfx_read_pixel_i8;
		gfx_copy_rectangle = gfx_copy_rectangle_i8;
	}
	else if (GFX_VIDEO_MODE.depth == 15 || GFX_VIDEO_MODE.depth == 16) {
		gfx_draw_pixel = gfx_draw_pixel555_565;
		gfx_read_pixel = gfx_read_pixel555_565;
		gfx_copy_rectangle = gfx_copy_rectangle555_565;
	}
	else if (GFX_VIDEO_MODE.depth == 24) {
		gfx_draw_pixel = gfx_draw_pixel888;
		gfx_read_pixel = gfx_read_pixel888;
		gfx_copy_rectangle = gfx_copy_rectangle888;
	}
	else if (GFX_VIDEO_MODE.depth == 32) {
		gfx_draw_pixel = gfx_draw_pixel8888;
		gfx_read_pixel = gfx_read_pixel8888;
		gfx_copy_rectangle = gfx_copy_rectangle8888;
	}
	else {
		/*
			*_stub functions do nothing, they are needed
			as placeholders if we have not defined a known video mode
		*/
		gfx_draw_pixel = gfx_draw_pixel_stub;
		gfx_read_pixel = gfx_read_pixel_stub;
		gfx_copy_rectangle = gfx_copy_rectangle_stub;
	}
}
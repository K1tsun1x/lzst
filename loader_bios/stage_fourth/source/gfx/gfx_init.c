#include <gfx.h>

extern video_mode_t GFX_VIDEO_MODE;
extern uint8_t* GFX_BUFFER;

extern void gfx_draw_pixel_i8(int x, int y, uint8_t r, uint8_t g, uint8_t b);
extern void gfx_draw_pixel555_565(int x, int y, uint8_t r, uint8_t g, uint8_t b);
extern void gfx_draw_pixel888(int x, int y, uint8_t r, uint8_t g, uint8_t b);
extern void gfx_draw_pixel8888(int x, int y, uint8_t r, uint8_t g, uint8_t b);
extern void gfx_draw_pixel_stub(int x, int y, uint8_t r, uint8_t g, uint8_t b);

extern void gfx_read_pixel_i8(int x, int y, uint8_t* r, uint8_t* g, uint8_t* b);
extern void gfx_read_pixel555_565(int x, int y, uint8_t* r, uint8_t* g, uint8_t* b);
extern void gfx_read_pixel888(int x, int y, uint8_t* r, uint8_t* g, uint8_t* b);
extern void gfx_read_pixel8888(int x, int y, uint8_t* r, uint8_t* g, uint8_t* b);
extern void gfx_read_pixel_stub(int x, int y, uint8_t* r, uint8_t* g, uint8_t* b);

extern void gfx_copy_rectangle_i8(int src_x, int src_y, int dst_x, int dst_y, size_t width, size_t height);
extern void gfx_copy_rectangle555_565(int src_x, int src_y, int dst_x, int dst_y, size_t width, size_t height);
extern void gfx_copy_rectangle888(int src_x, int src_y, int dst_x, int dst_y, size_t width, size_t height);
extern void gfx_copy_rectangle8888(int src_x, int src_y, int dst_x, int dst_y, size_t width, size_t height);
extern void gfx_copy_rectangle_stub(int src_x, int src_y, int dst_x, int dst_y, size_t width, size_t height);

void gfx_init(video_mode_t* video_mode) {
	GFX_VIDEO_MODE = *video_mode;
	GFX_BUFFER = (uint8_t*)GFX_VIDEO_MODE.framebuffer;
	
	const video_mode_t* vm = &GFX_VIDEO_MODE;
	if (vm->depth == 8) {
		gfx_draw_pixel = gfx_draw_pixel_i8;
		gfx_read_pixel = gfx_read_pixel_i8;
		gfx_copy_rectangle = gfx_copy_rectangle_i8;
	}
	else if (vm->depth == 15 || vm->depth == 16) {
		gfx_draw_pixel = gfx_draw_pixel555_565;
		gfx_read_pixel = gfx_read_pixel555_565;
		gfx_copy_rectangle = gfx_copy_rectangle555_565;
	}
	else if (vm->depth == 24) {
		gfx_draw_pixel = gfx_draw_pixel888;
		gfx_read_pixel = gfx_read_pixel888;
		gfx_copy_rectangle = gfx_copy_rectangle888;
	}
	else if (vm->depth == 32) {
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
#pragma once
#ifndef __VIDEO_MODE_H
#define __VIDEO_MODE_H

#include "video_mode_type.h"

typedef struct _video_mode_t {
	uint16_t					number;
	video_mode_type_t			type;
	bool						indexed;
	uint32_t					width;
	uint32_t					height;
	uint32_t					depth;
	uint16_t					pitch;
	uint8_t						bits_red;
	uint8_t						shift_red;
	uint8_t						bits_green;
	uint8_t						shift_green;
	uint8_t						bits_blue;
	uint8_t						shift_blue;
	union {
		uint8_t					bits_alpha;
		uint8_t					bits_reserved;
	};
	union {
		uint8_t					shift_alpha;
		uint8_t					shift_reserved;
	};
	uint32_t					framebuffer;
} video_mode_t;

#endif
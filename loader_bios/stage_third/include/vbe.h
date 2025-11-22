#pragma once
#ifndef __VESA_H
#define __VESA_H

#include "vbe_mode_attribute.h"
#include "vbe_info.h"
#include "vbe_mode_info.h"
#include "video_mode.h"

// { 'A', 'S', 'E', 'V' }
#define VBE_INFO_SIGNATURE				0x41534556

/**
 * @return Returns true and fills the buffer if VBE is present
 */
EXTERN_C bool LOADERCALL vbe_get_info(vbe_info_t* buffer);

/**
 * @return Returns true and fills the buffer if VBE is present
 */
EXTERN_C bool LOADERCALL vbe_get_mode_info(uint16_t mode, vbe_mode_info_t* buffer);

void vbe_find_best_video_mode(
	const vbe_info_t* vbe_info,
	size_t width,
	size_t height,
	size_t depth,
	video_mode_t* best_video_mode
);

bool LOADERCALL vbe_set_video_mode(uint16_t number);

#endif
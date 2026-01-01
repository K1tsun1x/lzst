#pragma once
#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
#define XTRN_C					extern "C"
#define CONST_CAST(type, ...)		const_cast<type>(__VA_ARGS__)
#define ENUM_TYPE(type)				: type
#else
#define XTRN_C					extern
#define CONST_CAST(type, ...)		(type)(__VA_ARGS__)
#define ENUM_TYPE(type)
#endif

#if defined(__GNUC__) || defined(__clang__)
#define __GNUC_CLANG__
#define __stdcall					__attribute__((__stdcall__))
#define __cdecl						__attribute__((__cdecl__))
#define ALIGNED(...)				__attribute__((__aligned__(__VA_ARGS__)))
#elif defined(_MSC_VER)
#define ALIGNED(...)				__declspec(align(__VA_ARGS__))
#endif

/**
 * @note Calling convetion
 * 
 * `LOADERCALL` (stack-based; callee preserves all registers except EAX/AX/AL, which is used for the return value)
 */
#define LOADERCALL

#endif
#pragma once
#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#if !defined(__GNUC__) && !defined(__clang__)
#error This compiler is not supported!
#endif

#ifdef __cplusplus
#define XTRN_C					extern "C"
#define XTRN_ONLY_CPP				XTRN_C
#define CONST_CAST(type, ...)		const_cast<type>(__VA_ARGS__)
#define ENUM_TYPE(type)				: type
#else
#define XTRN_C					extern
#define XTRN_ONLY_CPP
#define CONST_CAST(type, ...)		(type)(__VA_ARGS__)
#define ENUM_TYPE(type)
#endif

#define UNREFERENCED_PARAMETER(...)	((void)(__VA_ARGS__))

#define ARRAY_LENGTH_VARIABLE		1

#define __stdcall					__attribute__((__stdcall__))
#define __cdecl						__attribute__((__cdecl__))
#define ALIGNED(...)				__attribute__((__aligned__(__VA_ARGS__)))
#define NORETURN					__attribute__((__noreturn__))
#define UNREACHABLE					__builtin_unreachable

#ifdef __x86_64__
#define X64
#endif

/**
 * @note Calling convetion
 * 
 * `LOADERCALL` (stack-based; callee preserves all registers except EAX/AX/AL, which is used for the return value)
 */
#define LOADERCALL

#define OFFSET_OF($st_type, $field)	((uintptr_t)(&((($st_type*)0)->$field)))

typedef __CHAR32_TYPE__				char32_t;

#endif
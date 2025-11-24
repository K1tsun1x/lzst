#pragma once
#ifndef __FPU_H
#define __FPU_H

#include <typedefs.h>

EXTERN_C void LOADERCALL fpu_init(bool osfxsr, bool osxmmexcpt, bool osxsave);

#endif
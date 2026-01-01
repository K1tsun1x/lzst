#pragma once
#ifndef __FPU_H
#define __FPU_H

#include <typedefs.h>

XTRN_C void LOADERCALL fpu_init(bool osfxsr, bool osxmmexcpt, bool osxsave);

#endif
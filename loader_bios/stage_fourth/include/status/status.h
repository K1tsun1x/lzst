#pragma once
#ifndef __STATUS_H
#define __STATUS_H

#include <typedefs.h>

#define STATUS_UNREACHABLE				-4l
#define STATUS_INVALID_HEADER			-3l
#define STATUS_NOT_FOUND				-2l
#define STATUS_NO_MEMORY				-1l
#define STATUS_OK						0l


typedef long			status_t;

#endif
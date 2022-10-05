#pragma once

#ifdef _WIN32
#include "System_Win32.h"
#include "System_Common.h"
#else
#include "System_Emscripten.h"
#endif

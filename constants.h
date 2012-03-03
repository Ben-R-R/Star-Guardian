#ifndef CONSTANTS_H
#define CONSTANTS_H

//#define LINUX
#if defined LINUX
#include <SDL/SDL.h>
#else
#include "SDL.h"
#endif

const float PI_f = 3.14159265358979323846f;

#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1024
#define SCREEN_BPP 32 
#define TARGET_MS_PER_FRAME 50

#endif

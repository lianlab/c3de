#ifndef COMMON_DEFS
#define COMMON_DEFS

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#ifdef _DEBUG
#define WINDOWED true
#else
#define WINDOWED false
#endif

#ifndef NULL
#define NULL 0

#endif

#define ROUND_FLOAT(x) {(int)(x + 0.5f)}

#define HACK_FROM_SCRATCH 1

//#define EPSILON 0.001f
#define FAR_Z 1000.0f

#endif
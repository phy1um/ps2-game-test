/**
 * definition of special playstation 2 values
 */
#ifndef PS2_HEADER_H
#define PS2_HEADER_H

#include <gsToolkit.h>

#define gs_rgb(r,g,b) GS_SETREG_RGBA(r,g,b,0x80)

extern u64 COL_CLEAR;
extern u64 COL_NEUTRAL;

#endif


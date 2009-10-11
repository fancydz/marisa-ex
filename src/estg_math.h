#ifndef ESTG_MATH_H
#define ESTG_MATH_H

#pragma warning(disable:4305 4244)

#include <math.h>
#include <hge.h>

inline float v2a(float x,float y)
{
	if(fabs(x)<1e-7) x=1e-7;
	if(x>0) return atan(y/x)*M_2_PI;
	else return atan(y/x)*M_2_PI+2.0;
}

#endif

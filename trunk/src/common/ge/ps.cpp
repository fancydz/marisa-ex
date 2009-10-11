#include "ps.h"

ge_ps::ge_ps(pic* image,float x0,float y0,int _layer,int life_time)
{
	img=image;
	x=x0;
	y=y0;
	_life_time=life_time;
	layer=_layer;
}

void ge_ps::loop()
{
	if(age==_life_time) destroy();
}

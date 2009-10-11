#include "bubble.h"
#include <ESTG.h>

bubble::bubble(float x0,float y0,pic* image,int life_time,float start_size,float end_size,DWORD start_color,DWORD end_color,int _layer)
{
	x=x0;y=y0;
	life=life_time;
	s1=start_size;
	s2=end_size;
	c1=start_color;
	c2=end_color;
	img=image;
	layer=_layer;
}

void bubble::draw()
{
	float size,t;
	DWORD color;
	t=(double(age))/life;
	size=(1-t)*s1+t*s2;
	color= ((((((c1>>24)&0x000000FF)*(life-age))+(((c2>>24)&0x000000FF)*age))/life)<<24)
	      +((((((c1>>16)&0x000000FF)*(life-age))+(((c2>>16)&0x000000FF)*age))/life)<<16)
	      +((((((c1>> 8)&0x000000FF)*(life-age))+(((c2>> 8)&0x000000FF)*age))/life)<< 8)
	      +((((((c1>> 0)&0x000000FF)*(life-age))+(((c2>> 0)&0x000000FF)*age))/life)<< 0);
	img->SetColor(color);
	img->RenderEx(x2scr(real_x),y2scr(real_y),rot,size);
	img->SetColor(0xFFFFFFFF);
}

void bubble::loop()
{
	if(age==life) destroy();
}

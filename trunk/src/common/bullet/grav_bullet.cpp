#include "grav_bullet.h"

grav_bullet::grav_bullet(float x0,float y0,float vx0,float vy0,pic* image,float g)
{
	cx=x0;
	cy=y0;
	_vx=vx0/60.0;
	_vy=vy0/60.0;
	img=image;
	_g=g/3600.0;
}

void grav_bullet::loop()
{
	x=_vx*age;
	y=_vy*age+0.5*_g*age*age;
}

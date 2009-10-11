#include "straight_bullet.h"
#include <estg_math.h>
#include <ESTG.h>

straight_bullet::straight_bullet(float x0,float y0,float angle,float speed,pic* image,
	                             bool aim,float delay,float spin,float rot0,int _layer)
{
	if(aim) angle+=v2a(estg->self->x-x0,estg->self->y-y0);
	cx=x0;cy=y0;crot=angle;
	_speed=speed/60.0;
	_spin=spin/60.0;
	img=image;
	age=-int(delay);
	rot=y=x=0.0;
	_rot=rot0;
	if(fabs(_rot)>MAX_ANGLE) _rot=hge->Random_Float(0.0,4.0);
	layer=_layer;
}

straight_bullet::straight_bullet(float x0,float y0,float angle,float speed,pic* image,
	                             bool aim,float delay,float spin,int _layer)
{
	if(aim) angle+=v2a(estg->self->x-x0,estg->self->y-y0);
	cx=x0;cy=y0;crot=angle;
	_speed=speed/60.0;
	_spin=spin/60.0;
	img=image;
	age=-int(delay);
	rot=y=x=0.0;
	_rot=0.0;
	if(fabs(_rot)>MAX_ANGLE) _rot=hge->Random_Float(0.0,4.0);
	layer=_layer;
}

straight_bullet::straight_bullet(float x0,float y0,float angle,float speed,pic* image,
	                             bool aim,float delay,int _layer)
{
	if(aim) angle+=v2a(estg->self->x-x0,estg->self->y-y0);
	cx=x0;cy=y0;crot=angle;
	_speed=speed/60.0;
	_spin=0.0;
	img=image;
	age=-int(delay);
	rot=y=x=0.0;
	_rot=0.0;
	if(fabs(_rot)>MAX_ANGLE) _rot=hge->Random_Float(0.0,4.0);
	layer=_layer;
}

straight_bullet::straight_bullet(float x0,float y0,float angle,float speed,pic* image,
	                             bool aim,int _layer)
{
	if(aim) angle+=v2a(estg->self->x-x0,estg->self->y-y0);
	cx=x0;cy=y0;crot=angle;
	_speed=speed/60.0;
	_spin=0.0;
	img=image;
	rot=y=x=0.0;
	_rot=0.0;
	if(fabs(_rot)>MAX_ANGLE) _rot=hge->Random_Float(0.0,4.0);
	layer=_layer;
}

straight_bullet::straight_bullet(float x0,float y0,float angle,float speed,pic* image,
	                             int _layer)
{
	cx=x0;cy=y0;crot=angle;
	_speed=speed/60.0;
	_spin=0.0;
	img=image;
	rot=y=x=0.0;
	_rot=0.0;
	if(fabs(_rot)>MAX_ANGLE) _rot=hge->Random_Float(0.0,4.0);
	layer=_layer;
}

void straight_bullet::loop()
{
	rot=_rot+age*_spin;
	x=age*_speed;
}


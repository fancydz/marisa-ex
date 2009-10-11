#include "straight_self_bullet.h"
#include <ESTG.h>
#include <common\ge\ps.h>

straight_self_bullet::straight_self_bullet(int type,float dmg,float x0,float y0,float angle,float speed,pic* image,float delay)
{
	hp=dmg;
	_speed=speed/60.0;
	age=-int(delay);
	rot=0.0;
	crot=angle;
	img=image;
	startx=x0;
	starty=y0;
	if(type<0) type=0;
	if(type>2) type=2;
	_type=type;
}

void straight_self_bullet::loop()
{
	if(age==1)
	{
		cx=estg->self->x+startx;
		cy=estg->self->y+starty;
		update_xy();
		aim();
	}
	if(age==10)
		aim();
	x=age*_speed;
}

void straight_self_bullet::aim()
{
	if((estg->self->sres.blt["tar1"]!=0)&&_type==1)
	{
		cx=real_x;
		cy=real_y;
		crot=v2a(((bullet*)(estg->self->sres.blt["tar1"]))->real_x-cx,((bullet*)(estg->self->sres.blt["tar1"]))->real_y-cy);
		age=1;
		return;
	}
	if((estg->self->sres.blt["tar2"]!=0)&&_type==2)
	{
		cx=real_x;
		cy=real_y;
		crot=v2a(((bullet*)(estg->self->sres.blt["tar2"]))->real_x-cx,((bullet*)(estg->self->sres.blt["tar2"]))->real_y-cy);
		age=1;
		return;
	}
}

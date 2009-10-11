#include "green_dam_bullet_B.h"
#include <ESTG.h>
#include <common\ge\ps.h>

green_dam_bullet_B::green_dam_bullet_B(int type,double dmg,double x0,double y0,double angle,double speed,pic* image,double delay)
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

void green_dam_bullet_B::loop()
{
	if(age==0)
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

void green_dam_bullet_B::aim()
{
	if((estg->self->sres.blt["tar1"]!=0)&&_type==1)
	{
		cx=real_x;
		cy=real_y;
		crot=v2a(((bullet*)(estg->self->sres.blt["tar1"]))->real_x-cx,((bullet*)(estg->self->sres.blt["tar1"]))->real_y-cy);
		age=0;
		return;
	}
	if((estg->self->sres.blt["tar2"]!=0)&&_type==2)
	{
		cx=real_x;
		cy=real_y;
		crot=v2a(((bullet*)(estg->self->sres.blt["tar2"]))->real_x-cx,((bullet*)(estg->self->sres.blt["tar2"]))->real_y-cy);
		age=0;
		return;
	}
}

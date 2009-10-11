#include "item.h"
#include <ESTG.h>
#include <common\ge\ps.h>

item::item(bullet* p)
{
	attracted=true;
	suffer=false;
	hostile=false;
	cx=p->real_x;
	cy=p->real_y;
	img=res->YONG[0];
	_v0=0.1/60.0;
	_v1=0.3/60.0;
	_t0=1.0*60.0;
	track_speed=0.015;
}

void item::loop()
{
	if(attracted)
	{
		float dx,dy,dr;
		dx=estg->self->real_x-real_x;
		dy=estg->self->real_y-real_y;
		dr=sqrt(dx*dx+dy*dy);
		x+=dx/dr*track_speed;
		y+=dy/dr*track_speed;
	}
	else
		y=-_v0*age+(_v1-_v0)*_t0*(1-exp(-age/_t0));
	if(real_y<-0.64) dead=true;
	if(estg->self->real_y>0.3)
	{
		attracted=true;
		track_speed=0.015;
	}
}

void item::collide(bullet* sufferer)
{
   	estg->play_se("se_item01",0.2);
	dead=true;
}

bullet_bonus::bullet_bonus(bullet* p):item(p)
{
	type=(estg->self->sts+104.5)/19;
	img=res->YONG[type];
}

void bullet_bonus::collide(bullet *sufferer)
{
	item::collide(sufferer);
	if(estg->self->slow) estg->self->sts+=1.0;
	else estg->self->sts-=1.0;
	if(estg->self->sts>100.0) estg->self->sts=100.0;
	if(estg->self->sts<-100.0) estg->self->sts=-100.0;
}

bullet_corpse::bullet_corpse(bullet* p):item(p)
{
	img=res->img["yin"];
}

void bullet_corpse::collide(bullet *sufferer)
{
	dead=true;
	estg->play_se("se_item00",0.2);
}

point::point(bullet* p):item(p)
{
	type=(estg->self->sts+104.5)/19;
	img=res->POINT[type];
	attracted=false;
}

void point::collide(bullet *sufferer)
{
	dead=true;
	estg->play_se("se_item00",0.2);
	if(estg->self->slow) estg->self->sts+=1.0;
	else estg->self->sts-=1.0;
	if(estg->self->sts>100.0) estg->self->sts=100.0;
	if(estg->self->sts<-100.0) estg->self->sts=-100.0;
}

void point::loop()
{
	item::loop();
	if(age<=30) rot=age/3.75+1.0;
	if(!attracted&&is_collide(this,estg->self,0.1))
	{
		attracted=true;
		track_speed=0.007;
	}
}
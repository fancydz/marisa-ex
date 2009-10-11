#include "cannon.h"
#include <ESTG.h>

cannon::cannon(float x0,float vx,float vy,float g)
{
	y=-0.7;x=x0;
	_vx=vx;_vy=vy;
	_g=g;
	hide=true;
	hostile=true;
}

void cannon::loop()
{
	int i;
	if(age==30)
		for(i=0;i<10;i++)
			estg->add(new cartridge(-1,6*i,x,y,_vx,_vy,_g));
	if(age==90)
	{
		estg->play_se("se_lazer00",0.3);
		for(i=0;i<10;i++)
			estg->add(new cartridge(+1,6*i,x,y,_vx,_vy,_g));
		dead=true;
	}
}

cartridge::cartridge(int type,int delay,float x0,float y0,float vx,float vy,float g)
{
	cx=x0;cy=y0;
	_vx=vx;_vy=vy;
	_g=g;
	age=-delay;
	auto_clear=false;
	if(type<0)
	{
		img=res->img["cannon-warn"];
		attack=false;
		suffer=false;
		layer--;
	}
	else
	{
		img=res->img["cannon"];
	}
}

void cartridge::loop()
{
	float t=age/60.0;
	if(age>120) dead=true;
	if(age>60) return;
	x=t*_vx;
	y=t*_vy+0.5*t*t*_g;
}

#include "girl.h"
#include <estg_math.h>
#include <ESTG.h>

girl::girl(int type,bool aura)
{
	if(type<0) type=0;
	if(type>15) type=15;
	_type=type;
	_aura=aura;
	img=res->GIRL_IMG[type][0];
}

void girl::draw()
{
	if(hide||(age<=0)) return;
	if(_aura)
		res->img["enemy_aura"]->RenderEx(x2scr(real_x),y2scr(real_y),0.0,0.85+0.15*sin(age/16.0));
	bool xflip=delta_x>0;
	float xspeed=fabs(delta_x);
	if(xspeed<SLOPE_SPEED)
	{
		res->GIRL_IMG[_type][(age/4)%4]->SetFlip(xflip,false);
		res->GIRL_IMG[_type][(age/4)%4]->Render(x2scr(real_x),y2scr(real_y));
	}
	else if(xspeed<SLOPE_SPEED*2)
	{
		res->GIRL_IMG[_type][7]->SetFlip(xflip,false);
		res->GIRL_IMG[_type][7]->Render(x2scr(real_x),y2scr(real_y));
	}
	else if(xspeed<SLOPE_SPEED*3)
	{
		res->GIRL_IMG[_type][6]->SetFlip(xflip,false);
		res->GIRL_IMG[_type][6]->Render(x2scr(real_x),y2scr(real_y));
	}
	else if(xspeed<SLOPE_SPEED*4)
	{
		res->GIRL_IMG[_type][5]->SetFlip(xflip,false);
		res->GIRL_IMG[_type][5]->Render(x2scr(real_x),y2scr(real_y));
	}
	else
	{
		res->GIRL_IMG[_type][4]->SetFlip(xflip,false);
		res->GIRL_IMG[_type][4]->Render(x2scr(real_x),y2scr(real_y));
	}
}

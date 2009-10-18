#include "laser.h"
#include <ESTG.h>

laser::laser(int type)
{
	hostile=true;
	attack=true;
	_type=type;
	layer=ENEMY_BULLET_LAYER-1;
	aura_spin=0.05;
	c=0xFFFFFFFF;
	rot=0.0;
	r0=0.01;
	r=0.0;
	l1=0.2;
	l2=0.5;
	node=0.5;
	turn_on_sts=turn_off_sts=0;
	turn_on_time=turn_off_time=1;
	has_aura=false;
}

void laser::loop()
{
	//
	if(turn_on_sts>0)
	{
		turn_on_sts--;
		r=r0*(turn_on_time-turn_on_sts)/turn_on_time;
	}
	if(turn_off_sts>0)
	{
		turn_off_sts--;
		r=r0*turn_off_sts/turn_off_time;
	}
	//
	if(turn_on_sts!=0||turn_off_sts!=0||(!attack)||(r/r0<0.01)) return;
	//
	float dx,dy,xx,yy;
	dx=estg->self->real_x-real_x;
	dy=estg->self->real_y-real_y;
	xx= dx*cos(M_PI_2*(rot+crot))+dy*sin(M_PI_2*(rot+crot));
	yy=-dx*sin(M_PI_2*(rot+crot))+dy*cos(M_PI_2*(rot+crot));
	//
	if(xx>0&&xx<l1&&fabs(yy)<(xx/l1*r*0.5))
		estg->self->miss();
	if(xx>l1&&xx<(l1+l2+l2)&&fabs(yy)<(r*0.5))
		estg->self->miss();
	if(xx>(l1+l2+l2)&&xx<(l1+l2+l2+l1)&&fabs(yy)<((l1+l2+l2+l1-xx)/l1*r*0.5))
		estg->self->miss();
	if(age%10==0)
	{
		if(xx>0&&xx<l1&&fabs(yy)<(xx/l1*r*0.5+0.05))
			estg->self->graze();
		if(xx>l1&&xx<(l1+l2+l2)&&fabs(yy)<(r*0.5+0.05))
			estg->self->graze();
		if(xx>(l1+l2+l2)&&xx<(l1+l2+l2+l1)&&fabs(yy)<((l1+l2+l2+l1-xx)/l1*r*0.5+0.05))
			estg->self->graze();
	}
	//
}

void laser::turn_on(int t)
{
	if(turn_on_sts*turn_off_sts!=0) return;
	if(r/r0>0.99) return;
	turn_on_sts=turn_on_time=t;
}

void laser::turn_off(int t)
{
	if(turn_on_sts!=0||turn_off_sts!=0) return;
	if(r/r0<0.01) return;
	turn_off_sts=turn_off_time=t;
}

void laser::draw()
{
	//
	if(age<1) return;
	//
	if(node>0&&has_aura)
		res->img["enemy_aura"]->RenderEx(x2scr(real_x),y2scr(real_y),aura_spin*estg->ticker,0.5*node);
	//
	res->LASER->SetTextureRect(0,_type*32,256,32);
	//
	res->LASER->SetDisplacement(0,0,X_STRETCH*((0)*cos(M_PI_2*(rot+crot))-r*-sin(M_PI_2*(rot+crot))),X_STRETCH*((0)*-sin(M_PI_2*(rot+crot))+r*cos(M_PI_2*(rot+crot))),HGEDISP_TOPLEFT);
	res->LASER->SetDisplacement(1,0,X_STRETCH*((l1)*cos(M_PI_2*(rot+crot))-r*-sin(M_PI_2*(rot+crot))),X_STRETCH*((l1)*-sin(M_PI_2*(rot+crot))+r*cos(M_PI_2*(rot+crot))),HGEDISP_TOPLEFT);
	res->LASER->SetDisplacement(2,0,X_STRETCH*((l1+l2)*cos(M_PI_2*(rot+crot))-r*-sin(M_PI_2*(rot+crot))),X_STRETCH*((l1+l2)*-sin(M_PI_2*(rot+crot))+r*cos(M_PI_2*(rot+crot))),HGEDISP_TOPLEFT);
	res->LASER->SetDisplacement(3,0,X_STRETCH*((l1+l2+l2)*cos(M_PI_2*(rot+crot))-r*-sin(M_PI_2*(rot+crot))),X_STRETCH*((l1+l2+l2)*-sin(M_PI_2*(rot+crot))+r*cos(M_PI_2*(rot+crot))),HGEDISP_TOPLEFT);
	res->LASER->SetDisplacement(4,0,X_STRETCH*((l1+l2+l2+l1)*cos(M_PI_2*(rot+crot))-r*-sin(M_PI_2*(rot+crot))),X_STRETCH*((l1+l2+l2+l1)*-sin(M_PI_2*(rot+crot))+r*cos(M_PI_2*(rot+crot))),HGEDISP_TOPLEFT);
	//
	res->LASER->SetDisplacement(0,1,X_STRETCH*((0)*cos(M_PI_2*(rot+crot))+r*-sin(M_PI_2*(rot+crot))),X_STRETCH*((0)*-sin(M_PI_2*(rot+crot))-r*cos(M_PI_2*(rot+crot))),HGEDISP_TOPLEFT);
	res->LASER->SetDisplacement(1,1,X_STRETCH*((l1)*cos(M_PI_2*(rot+crot))+r*-sin(M_PI_2*(rot+crot))),X_STRETCH*((l1)*-sin(M_PI_2*(rot+crot))-r*cos(M_PI_2*(rot+crot))),HGEDISP_TOPLEFT);
	res->LASER->SetDisplacement(2,1,X_STRETCH*((l1+l2)*cos(M_PI_2*(rot+crot))+r*-sin(M_PI_2*(rot+crot))),X_STRETCH*((l1+l2)*-sin(M_PI_2*(rot+crot))-r*cos(M_PI_2*(rot+crot))),HGEDISP_TOPLEFT);
	res->LASER->SetDisplacement(3,1,X_STRETCH*((l1+l2+l2)*cos(M_PI_2*(rot+crot))+r*-sin(M_PI_2*(rot+crot))),X_STRETCH*((l1+l2+l2)*-sin(M_PI_2*(rot+crot))-r*cos(M_PI_2*(rot+crot))),HGEDISP_TOPLEFT);
	res->LASER->SetDisplacement(4,1,X_STRETCH*((l1+l2+l2+l1)*cos(M_PI_2*(rot+crot))+r*-sin(M_PI_2*(rot+crot))),X_STRETCH*((l1+l2+l2+l1)*-sin(M_PI_2*(rot+crot))-r*cos(M_PI_2*(rot+crot))),HGEDISP_TOPLEFT);
	//
	res->LASER->SetColor(0,0,c);
	res->LASER->SetColor(1,0,c);
	res->LASER->SetColor(2,0,c);
	res->LASER->SetColor(3,0,c);
	res->LASER->SetColor(4,0,c);
	res->LASER->SetColor(0,1,c);
	res->LASER->SetColor(1,1,c);
	res->LASER->SetColor(2,1,c);
	res->LASER->SetColor(3,1,c);
	res->LASER->SetColor(4,1,c);
	//
	res->LASER->Render(x2scr(real_x),y2scr(real_y));
	//
	if(node>0)
	{
		res->PREMASK[_type]->RenderEx(x2scr(real_x),y2scr(real_y),estg->ticker*0.01,node);
		res->PREMASK[_type]->RenderEx(x2scr(real_x),y2scr(real_y),-estg->ticker*0.01,node);
	}
	//
}
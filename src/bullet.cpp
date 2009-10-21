#include "bullet.h"
#include <ESTG.h>
#include <common\ge\bubble.h>
#include <common\ge\ps.h>
#include <estg_math.h>
#include <common\item\item.h>

bullet::bullet()
{
	x=y=cx=cy=crot=0.0;
	rot=1.0;
	scale=1.0;
	real_x=real_y=0.0;
	age=0;
	hide=false;
	auto_clear=true;
	dead=false;
	label="none";
	grazed=false;
	attack=true;
	suffer=true;
	hostile=false;
	attr=ENEMY_BULLET;
	layer=ENEMY_BULLET_LAYER;
	img=res->img["err"];
	ps=0;
	master=0;
	hp=MAX_HP;
	drop_num=1;
	dmg_factor=1.0;
}

void bullet::collide(bullet* sufferer)
{
}

bullet::~bullet()
{
	if(ps!=0)
	{
 		if(ps->GetParticlesAlive()!=0)
			estg->add(new ps_agent(this));
 		else delete ps;
	}
}

void bullet::loop()
{
}

void bullet::draw()
{
	if(hide||(age<=0)) return;
	if((img->ps!=0)&&ps==0)
	{
		ps=new hgeParticleSystem(*(img->ps));
		ps->MoveTo(x2scr(real_x),y2scr(real_y));
		ps->Fire();
	}
	if(ps==0)
		if(!img->no_rot)
			img->RenderEx(x2scr(real_x),y2scr(real_y),M_PI_2*(1-rot-crot),scale);
		else
			img->RenderEx(x2scr(real_x),y2scr(real_y),0.0,scale);
	else
		ps->Render();
}

void bullet::destroy()
{
	dead=true;
}

void bullet::kill()
{
	dead=true;
}

void bullet::update_xy()
{
	float new_x,new_y;
	new_x=cx+x*cos(crot*M_PI_2)-y*sin(crot*M_PI_2);
	new_y=cy+y*cos(crot*M_PI_2)+x*sin(crot*M_PI_2);
	delta_x=new_x-real_x;
	delta_y=new_y-real_y;
	real_x=new_x;
	real_y=new_y;
}

ghost::ghost()
{
	auto_clear=false;
	attack=false;
	suffer=false;
	attr=GHOST;
	layer=BG_LAYER;
}

ether::ether()
{
	hide=true;
}

self_bullet::self_bullet()
{
	attr=SELF_BULLET;
	layer=SELF_BULLET_LAYER;
}

void self_bullet::collide(bullet* sufferer)
{
	estg->add(new ge_ps(res->SPARK[1],sufferer->real_x,sufferer->real_y,ENEMY_LAYER-1));
	estg->play_se("se_damage00",0.1);
	estg->data.score+=int(15*hp);
	if(sufferer->hp>0.0)
	{
		sufferer->hp-=(this->hp*sufferer->dmg_factor);
		if(sufferer->hp<=0.0) sufferer->kill();
	}
	destroy();
}

enemy_bullet::enemy_bullet()
{
	hostile=true;
}

void enemy_bullet::collide(bullet* sufferer)
{
	estg->self->miss();
}

void enemy_bullet::kill()
{
	dead=true;
	estg->add(new bullet_corpse(this));
}

enemy::enemy()
{
	auto_clear=false;
	hostile=true;
	attr=ENEMY;
	layer=ENEMY_LAYER;
}

void enemy::kill()
{
	dead=true;
	estg->add(new bubble(real_x,real_y,res->img["blue_bubble"],16,0.0,2.0,0xFFFFFFFF,0x00FFFFFF));
	estg->add(new ge_ps(res->SPARK2[5],real_x,real_y,ENEMY_LAYER-1));
	drop_point(drop_num);
	estg->play_se("se_enep00",0.25);
}

void enemy::drop_point(int num)
{
	if(num==1) estg->add(new point(this));
	else
	{
		int i;
		float ra=0.02/sin(M_PI/num);
		list<bullet*>::iterator iter;
		for(i=0;i<num;i++)
		{
			iter=estg->add(new point(this));
			(*iter)->cx+=ra*sin(2*M_PI*i/num);
			(*iter)->cy+=ra*cos(2*M_PI*i/num);
		}
	}
}

ps_agent::ps_agent(bullet* principal)
{
	ps=principal->ps;
	layer=principal->layer;
	x=principal->x;
	y=principal->y;
	rot=principal->rot;
	cx=principal->cx;
	cy=principal->cy;
	crot=principal->crot;
	ps->Stop();
}

void ps_agent::draw()
{
	ps->Render();
}

void ps_agent::loop()
{
	if(ps->GetParticlesAlive()==0) dead=true;
}

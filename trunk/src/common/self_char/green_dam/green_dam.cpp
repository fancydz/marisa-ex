#include "green_dam.h"
#include "..\\straight_self_bullet.h"
#include <ESTG.h>
#include <common\ge\ps.h>

#include <iostream>
using namespace std;

green_dam::green_dam()
{
	//load images
	char_tex=hge->Texture_Load("img\\green_dam.png");
	f1[0][0]=new pic(char_tex,0,0,32,48);
	f1[1][0]=new pic(char_tex,32,0,32,48);
	f1[2][0]=new pic(char_tex,64,0,32,48);
	f1[3][0]=new pic(char_tex,96,0,32,48);
	f2[0]=new pic(char_tex,0,48,32,48);
	f3[0]=new pic(char_tex,32,48,32,48);
	f4[0]=new pic(char_tex,64,48,32,48);
	f5[0][0]=new pic(char_tex,96,48,32,48);
	f5[1][0]=new pic(char_tex,128,48,32,48);
	f5[2][0]=new pic(char_tex,160,48,32,48);
	f5[3][0]=new pic(char_tex,192,48,32,48);
	f1[0][1]=new pic(char_tex,128,0,32,48);
	f1[1][1]=new pic(char_tex,160,0,32,48);
	f1[2][1]=new pic(char_tex,192,0,32,48);
	f1[3][1]=new pic(char_tex,224,0,32,48);
	f2[1]=new pic(char_tex,0,96,32,48);
	f3[1]=new pic(char_tex,32,96,32,48);
	f4[1]=new pic(char_tex,64,96,32,48);
	f5[0][1]=new pic(char_tex,96,96,32,48);
	f5[1][1]=new pic(char_tex,128,96,32,48);
	f5[2][1]=new pic(char_tex,160,96,32,48);
	f5[3][1]=new pic(char_tex,192,96,32,48);
	img=f1[0][0];
	sres.img["bullet_a"]=new pic(char_tex,0,144,16,64);
	sres.img["bullet_a"]->SetHotSpot(8,8);
	sres.img["bullet_a"]->SetColor(0x80FFFFFF);
	sres.img["bullet_b"]=new pic(char_tex,32,160,16,16);
	sres.img["bullet_b"]->SetColor(0x80FFFFFF);
	sres.img["l_minion"]=new pic(res->TEX["particles"],64,64,32,32,"img\\green_dam_ghost.psi");
	sres.img["r_minion"]=new pic(res->TEX["particles"],64,64,32,32,"img\\green_dam_ghost.psi");
	sres.img["attack_dust_a"]=new pic(char_tex,32,208,32,32,"img\\green_dam_attack_dust.psi");
	sres.img["attack_dust_b"]=new pic(char_tex,32,176,32,32,"img\\green_dam_attack_dust.psi");
	//attack cd of green_dam is 5 frame
	cd=5;
	//
}

green_dam::~green_dam()
{
	delete f1[0][0];
	delete f1[1][0];
	delete f1[2][0];
	delete f1[3][0];
	delete f2[0];
	delete f3[0];
	delete f4[0];
	delete f5[0][0];
	delete f5[1][0];
	delete f5[2][0];
	delete f5[3][0];
	delete f1[0][1];
	delete f1[1][1];
	delete f1[2][1];
	delete f1[3][1];
	delete f2[1];
	delete f3[1];
	delete f4[1];
	delete f5[0][1];
	delete f5[1][1];
	delete f5[2][1];
	delete f5[3][1];
	hge->Texture_Free(char_tex);
}

void green_dam::fire()
{
	if(!slow)
	{
		estg->add(new green_dam_bullet(0,1,-0.025,0,1.06,1.8,sres.img["bullet_a"]));
		estg->add(new green_dam_bullet(0,1,0,+0.03,1.0,1.8,sres.img["bullet_a"]));
		estg->add(new green_dam_bullet(0,1,+0.025,0,0.94,1.8,sres.img["bullet_a"]));
		
		estg->add(new green_dam_bullet(1,0.7,minion_x,minion_y,0.88,1.8,sres.img["bullet_b"]));
		estg->add(new green_dam_bullet(1,0.7,-minion_x,minion_y,1.12,1.8,sres.img["bullet_b"]));
	}
	else
	{
		estg->add(new green_dam_bullet(0,1,-0.022,0,1.01,1.8,sres.img["bullet_a"]));
		estg->add(new green_dam_bullet(0,1,0,0.03,1.0,1.8,sres.img["bullet_a"]));
		estg->add(new green_dam_bullet(0,1,+0.022,0,0.99,1.8,sres.img["bullet_a"]));
		
		estg->add(new green_dam_bullet(2,0.7,minion_x,minion_y,0.97,1.8,sres.img["bullet_b"]));
		estg->add(new green_dam_bullet(2,0.7,-minion_x,minion_y,1.03,1.8,sres.img["bullet_b"]));
	}
}

void green_dam::bomb()
{
	estg->add(new green_dam_bomb());
}

void green_dam::loop()
{
	minion_x=0.07*cos(double(lh_status)/LH_TRANSITION_TIME*1.3);
	minion_y=0.07*sin(double(lh_status)/LH_TRANSITION_TIME*1.3);
	sres.img["l_minion"]->ps->MoveTo(x2scr(x-minion_x),y2scr(y+minion_y));
	sres.img["l_minion"]->ps->Update(0.0166667);
	sres.img["l_minion"]->ps->Fire();
	sres.img["r_minion"]->ps->MoveTo(x2scr(x+minion_x),y2scr(y+minion_y));
	sres.img["r_minion"]->ps->Update(0.0166667);
	sres.img["r_minion"]->ps->Fire();
	self_char::act();
}

void green_dam::draw()
{
	self_char::draw();
	sres.img["l_minion"]->ps->Render();
	sres.img["r_minion"]->ps->Render();
}

green_dam_bullet::green_dam_bullet(int type,float dmg,float x0,float y0,float angle,float speed,pic* image,float delay)
:straight_self_bullet(type,dmg,x0,y0,angle,speed,image,delay)
{
}

void green_dam_bullet::collide(bullet* sufferer)
{
	if(_type==0)
		estg->add(new ge_ps(estg->self->sres.img["attack_dust_a"],real_x,real_y,ENEMY_LAYER+1));
	else
		estg->add(new ge_ps(estg->self->sres.img["attack_dust_b"],real_x,real_y,ENEMY_LAYER+1));
	self_bullet::collide(sufferer);
}

green_dam_bomb::green_dam_bomb()
{
	estg->play_se("se_gun00",0.5);
	clear_r=0.1;
	dying=(estg->self->dying_sts!=0);
	if(dying)
	{
		estg->shake(360);
		estg->self->inv(390);
	}
	else
	{
		estg->shake(240);
		estg->self->inv(270);
	}
}

void green_dam_bomb::loop()
{
	int i;
	for(i=0;i<3;i++)
	{
		estg->add(new green_dam_bomb_bullet(0,0,0,0,hge->Random_Float(0,4),hge->Random_Float(0.6,1.6),estg->self->sres.img["bullet_a"]));
		estg->add(new green_dam_bomb_bullet(3,0,0,0,hge->Random_Float(0,4),hge->Random_Float(0.6,1.6),estg->self->sres.img["bullet_b"]));
	}
	if(dying)
	{
		if(age<240)
		{
			clear_r+=0.012;
			list<bullet*>::iterator iter;
			for(i=0;i<MAX_LAYER;i++)
				for(iter=estg->blist[ENEMY_BULLET][i].begin();iter!=estg->blist[ENEMY_BULLET][i].end();iter++)
					if((*iter)->age>0&&(*iter)->suffer&&is_collide(*iter,estg->self,clear_r))
						(*iter)->kill();
		}
		if(age==120)
			clear_r=0.1;
		if(age==360)
		{
			estg->play_se("se_tan01",0.7);
			estg->kill_all_bullet();
			destroy();
		}
	}
	else
	{
		if(age<180)
		{
			clear_r+=0.016;
			list<bullet*>::iterator iter;
			for(i=0;i<MAX_LAYER;i++)
				for(iter=estg->blist[ENEMY_BULLET][i].begin();iter!=estg->blist[ENEMY_BULLET][i].end();iter++)
					if((*iter)->age>0&&(*iter)->suffer&&is_collide(*iter,estg->self,clear_r))
						(*iter)->kill();
		}
		if(age==90)
			clear_r=0.1;
		if(age==240)
		{
			estg->play_se("se_tan01",0.7);
			estg->kill_all_bullet();
			destroy();
		}
	}
}

green_dam_bomb_bullet::green_dam_bomb_bullet(int type,float dmg,float x0,float y0,float angle,float speed,pic *image,float delay)
:green_dam_bullet(type,dmg,x0,y0,angle,speed,image,delay)
{
	hp=0;
}

void green_dam_bomb_bullet::loop()
{
	straight_self_bullet::loop();
	hp=0.1*age;
	if(_type==3&&hge->Random_Int(0,5)==0)
		_type=hge->Random_Int(1,2);
}
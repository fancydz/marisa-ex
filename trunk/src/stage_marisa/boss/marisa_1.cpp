#include "marisa_1.h"
#include <ESTG.h>
#include <common\bullet\sector.h>
#include <common\bullet\circle.h>
#include <common\bullet\straight_bullet.h>
#include <common\ge\bubble.h>
#include "cannon.h"
#include "..\\marisa_bg.h"

marisa_1::marisa_1(float x0,float y0):marisa(x0,y0)
{
	age=-1;
	estg->destroy_all_enemy();
}

void marisa_1::loop()
{
	if(age>=0       && age<  SC_OS)
		sc_1(age);
	if(age>=SC_OS   && age<2*SC_OS)
		sc_3(age-SC_OS);
	if(age>=SC_OS*2 && age<3*SC_OS)
		sc_2(age-2*SC_OS);
	if(age>=SC_OS*3 && age<4*SC_OS)
		escape(age-3*SC_OS);
	boss::loop();
}

void marisa_1::sc_1(int t)
{
	int i;
	if(t==1)
	{
		start_card();
		sc_info.max_hp=hp=600;
		sc_info.time_1=0;
		sc_info.time_2=15;
		sc_info.time_3=45;
		estg->play_bgm(estg->sres.snd["0310"]->se,126.0,116.453878);
	}
	if(t==60) estg->set_bg(new marisa_bg());
	
	if(t%960==  1) move_to(0.0,0.3);
	if(t%960==241) move_to(0.2,0.35);
	if(t%960==481) move_to(0.0,0.3);
	if(t%960==721) move_to(-0.2,0.35);
	
	if(t>60)
	{
		if(t%6==0)
		{
			int dir=hge->Random_Int(0,1)*2-1;
			estg->add(new straight_bullet(0.55*dir,hge->Random_Float(-0.6,0.6),dir+1,hge->Random_Float(0.07,0.14),res->SSTAR[2*dir+4],false,0,2*dir,0,ENEMY_BULLET_LAYER));
		}
		if(t%120==10)
		{
			estg->add(new sector<>(real_x,real_y,0.0,0.43,res->SSTAR[13],true,3,7,0.025,0,0,0.04,20.0,0.0,0.0, 2.0,0.0,0.0,1000,0.0,0.0));
			estg->add(new sector<>(real_x,real_y,0.0,0.40,res->SSTAR[13],true,3,5,0.025,0,0,0.06, 0.0,0.0,0.0,-2.0,0.0,0.0,1000,0.0,0.0));
		}
		if(t%20==0)
			estg->play_se("se_tan00",0.15);
		if(t%180==60)
		{
			for(i=0;i<5;i++)
				estg->add(new cannon(hge->Random_Float(i*0.18-0.45,i*0.18-0.27),hge->Random_Float(-1.0,1.0),3.0,-3.0));
		}
	}
}

void marisa_1::sc_2(int t)
{
	int i;
	if(t==1)
	{
		start_card();
		sc_info.max_hp=hp=600;
		sc_info.time_1=0;
		sc_info.time_2=15;
		sc_info.time_3=45;
	}
	if(t==1) move_to(0.0,0.0);
	if(t==180)
	for(i=0;i<5;i++)
		estg->add(new marisa_1_2_minion(i));
}

void marisa_1::sc_3(int t)
{
	static int color_tick=0;
	if(t==1)
	{
		start_card();
		sc_info.max_hp=hp=600;
		sc_info.time_1=0;
		sc_info.time_2=15;
		sc_info.time_3=45;
	}
	//
	//move
	if(t%1500==  1) move_to(+0.0,0.4);
	if(t%1500==301) move_to(+0.3,0.45);
	if(t%1500==601) move_to(+0.1,0.35);
	if(t%1500==901) move_to(-0.1,0.45);
	if(t%1500==1201) move_to(-0.3,0.35);
	//
	//fire
	if(t>120&&t%80==20)
		estg->add(new marisa_1_3_minion((color_tick++)%5,true));
	if(t>120&&t%80==60)
		estg->add(new marisa_1_3_minion((color_tick++)%5,false));
	if(t>180&&t%40==30)
		estg->play_se("se_tan00",0.15);
	if(t>190&&t%5==2)
		estg->play_se("se_kira00",0.15);
	//
}

void marisa_1::escape(int t)
{
	hide_info=true;
	suffer=false;
	if(t==60)
	{
		estg->set_bg(new road_bg());
		estg->sres.val["bg_speed"]=0.125;
		move_to(0.54,0.64,120);
	}
	if(t==180) destroy();
}

marisa_1::~marisa_1()
{
	
}

void marisa_1::kill()
{
	drop_point(20);
	boss::kill();
}

marisa_1_2_minion::marisa_1_2_minion(int index)
{
	suffer=false;
	img=res->img["minion"];
	layer=ENEMY_LAYER+1;
	crot=index*0.8;
	vita=0.0;
	if(index==0) img_index=2;
	if(index==1) img_index=4;
	if(index==2) img_index=6;
	if(index==3) img_index=10;
	if(index==4) img_index=13;
}

void marisa_1_2_minion::loop()
{
	float f=fabs(float((age-20)%720-360))/360.0;
	if(age<20)
		x=age*0.005;
	else
		x=0.54-0.44*f*f*f;
	vita+=0.4/(x+0.2);
	if(vita>0.0)
	{
		if(img_index==2) estg->play_se("se_tan00",0.1);
		estg->add(new marisa_1_2_bullet(real_x,real_y,crot-2+0.5*cos(age/160.0),0.15,0,2,res->SSTAR[img_index]));
		if(x>0.45) estg->add(new sector<>(real_x,real_y,crot,0.2,res->SSTAR[img_index],false,6,3,0.2,0,0.02,0.04));
		vita-=7;
	}
	if(x>0.1) crot+=0.002/x;
	else crot+=0.02;
}


marisa_1_2_bullet::marisa_1_2_bullet(float x0,float y0,float angle,float v0,float v1,float t0,pic* image,float av)
:stage_marisa_wave_4_bullet(x0,y0,angle,v0,v1,t0,image)
{
	rot=hge->Random_Float(0,4.0);
	_av=av;
}

void marisa_1_2_bullet::loop()
{
	stage_marisa_wave_4_bullet::loop();
	rot+=_av;
}


marisa_1_3_minion::marisa_1_3_minion(int index,bool aim)
{
	layer=ENEMY_BULLET_LAYER+1;
	suffer=false;
	if(index==0){img_index=2;img=res->BSTAR[1];}
	if(index==1){img_index=4;img=res->BSTAR[2];}
	if(index==2){img_index=6;img=res->BSTAR[3];}
	if(index==3){img_index=10;img=res->BSTAR[5];}
	if(index==4){img_index=13;img=res->BSTAR[6];}
	x0=(index-2)*0.2;
	x1=(estg->self->y+0.64)/(0.64-estg->self->y)*(estg->self->x-x0)+estg->self->x;
	if(!aim)
	{
		x0=-x0;
		x1=-x1;
	}
}

void marisa_1_3_minion::loop()
{
	rot+=0.07;
	if(age==120) destroy();
	float f=age/120.0;
	f=f*(f+0.25)*0.8;
	x=x0*(1-f)+x1*f;
	y=0.64-1.28*f;
	if(age%4==2)
	{
		f=hge->Random_Float(0,1);
		estg->add(new marisa_1_2_bullet(real_x,real_y,hge->Random_Float(-1.0,1.0)*(real_y+1)+v2a(x1-x0,-1.28),0.3,0,2,res->SSTAR[img_index],(age%8-4)*0.03));
		(*(estg->add(new bubble(real_x,real_y,img,20,1,0.5,0xFFFFFFFF,0x00FFFFFF,layer=ENEMY_BULLET_LAYER))))->rot=rot;
	}
}
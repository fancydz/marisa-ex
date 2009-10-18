#include "boss.h"
#include <ESTG.h>

boss::boss(float x0,float y0)
{
	x1=x2=x=x0;y1=y2=y=y0;
	_time_spend=60;
	lr_status=1;
	cast_status=0;
	move_status=0;
	draw_age=0;
	int i;
	for(i=0;i<4;i++)
	{
		stay_img[i]=0;
		move_img[i]=0;
		cast_img[i]=0;
	}
	hostile=false;
	sc_info.max_hp=MAX_HP;
	sc_info.time_1=sc_info.time_2=sc_info.time_3=1000.0;
	hide_info=false;
	time_warner_created=false;
}

boss::~boss()
{

}

void boss::cast()
{
	cast_status=32;
}

void boss::loop()
{
	if(delta_x> 1e-4)
	{
		if(lr_status<0) lr_status=0;
		lr_status++;
	}
	if(delta_x<-1e-4)
	{
		if(lr_status>0) lr_status=0;
		lr_status--;
	}
	if(fabs(delta_x)<1e-4)
	{
		if(lr_status> 1) lr_status--;
		if(lr_status<-1) lr_status++;
	}
	if(lr_status> 17) lr_status= 17;
	if(lr_status<-17) lr_status=-17;
	if(cast_status>0) cast_status--;
	if(move_status>0) move_status--;
	float t=double(move_status)/_time_spend;
	x=x1*t+x2*(1-t);
	y=y1*t+y2*(1-t);
	draw_age++;
	if(age>1)
		if(estg->stage_master!=0)
			estg->stage_master->age--;
	//
	t=(age%SC_OS)/60.0;
	if(t<sc_info.time_1)
		dmg_factor=0.0;
	else if(t<sc_info.time_2)
		dmg_factor=(t-sc_info.time_1)/(sc_info.time_2-sc_info.time_1);
	else
		dmg_factor=1.0;
	estg->hp_bar=hp/sc_info.max_hp;
	if(estg->hp_bar>1.0) estg->hp_bar=1.0;
	estg->count_down_timer=sc_info.time_3-t;
	if(hide_info)
	{
		estg->count_down_timer=-1.0;
		estg->hp_bar=-1.0;
	}
	//
	if(sc_info.time_3<t) boss::kill();
	//
	if(sc_info.time_3<t+10.0)
	{
		if(!time_warner_created)
		{
			estg->add(new time_warner());
			time_warner_created=true;
		}
	}
	else
	{
		time_warner_created=false;
	}
	//
}

void boss::draw()
{
	int frame;
	bool flip=(lr_status<0);
	if(cast_status>0)
	{
		frame=cast_status/8;
		if(frame>=4) frame=3;
		cast_img[frame]->SetFlip(flip,false);
		cast_img[frame]->Render(x2scr(real_x),y2scr(real_y));
		return;
	}
	if(lr_status>1||lr_status<-1)
	{
		frame=(abs(lr_status)-2)/4;
		move_img[frame]->SetFlip(flip,false);
		move_img[frame]->Render(x2scr(real_x),y2scr(real_y));
		return;
	}
	frame=(draw_age/8)%4;
	stay_img[frame]->SetFlip(flip,false);
	stay_img[frame]->Render(x2scr(real_x),y2scr(real_y)+5*sin((draw_age%120)/120.0*M_PI*2));
	return;
}

void boss::move_to(float des_x,float des_y,int time_spend)
{
	x1=x;y1=y;
	x2=des_x;y2=des_y;
	_time_spend=move_status=time_spend;
}

void boss::kill()
{
	end_card();
	estg->play_se("se_enep01",0.25);
	age=(age/SC_OS)*SC_OS+SC_OS;
	hp=sc_info.max_hp=MAX_HP;
	sc_info.time_1=sc_info.time_2=sc_info.time_3=1000.0;
	estg->destroy_all_enemy();
}

void boss::start_card()
{
	estg->self->card_get=true;
	score_save=estg->data.score;
}

void boss::end_card()
{
	if(estg->self->card_get)
	{
		estg->data.score+=int((estg->data.score-score_save)*(CARD_FACTOR-1))*(1+estg->data.graze/GRAZE_FACTOR);
		estg->data.score+=int((sc_info.time_3-(age%SC_OS)/60.0)*TIME_BONUS)*(1+estg->data.graze/GRAZE_FACTOR);
		estg->self->card_get=false;
	}
}

time_warner::time_warner()
{
	hostile=true;
}

void time_warner::loop()
{
	if(age%60==10)
		estg->play_se("se_timeout",0.7);
}
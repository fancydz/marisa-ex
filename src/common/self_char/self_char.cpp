#include "self_char.h"
#include <ESTG.h>
#include <common\ge\bubble.h>
#include <common\ge\ps.h>

#include <iostream>

using namespace std;

self_char::self_char()
{
	sts=0.0;
	cd=5;
	current_cd=0;
	aura1_rot=aura2_rot=0.0;
	slow=false;
	no_bomb=false;
	high_speed=0.6/60.0;low_speed=0.3/60.0;
	x=SELF_STARTX;
	y=SELF_STARTY;
	auto_clear=false;
	attack=false;
	suffer=true;
	attr=SELF;
	layer=SELF_LAYER;
	lr_status=1;//-5 for full left,+5 for full right 
	lh_status=0;//0 for high speed,LH_TRANSITION_TIME for low speed
	aura1_img=res->img["self_aura1"];
	aura2_img=res->img["self_aura2"];
	graze_freq=0;
	inv_sts=0;
	dying_sts=0;
	card_get=false;
}

self_char::~self_char()
{
	
}

void self_char::act()
{
	int dx=0;
	int dy=0;
	float v_factor=1.0;
	//move
	if(estg->control.up) dy+=1;
	if(estg->control.down) dy-=1;
	if(estg->control.left) dx-=1;
	if(estg->control.right) dx+=1;
	if(dx*dy!=0) v_factor=0.707106781;
	slow=estg->control.slow;
	if(slow)
	{
		x+=dx*low_speed*v_factor;
		y+=dy*low_speed*v_factor;
	}
	else
	{
		x+=dx*high_speed*v_factor;
		y+=dy*high_speed*v_factor;
	}
	if(x>SELF_X_BORDER) x=SELF_X_BORDER;
	if(x<-SELF_X_BORDER) x=-SELF_X_BORDER;
	if(y>SELF_Y_BORDER) y=SELF_Y_BORDER;
	if(y<-SELF_Y_BORDER) y=-SELF_Y_BORDER;
	//
	// left/right status
	lr_status+=dx;
	if(lr_status>5) lr_status=5;
	if(lr_status<-5) lr_status=-5;
	if(lr_status==0) lr_status+=dx;
	if(dx==0)
	{
		if(lr_status>1) lr_status--;
		if(lr_status<-1) lr_status++;
	}
	//
	// low speed/high speed status
	if(lh_status==0 && slow) estg->add(new bubble(x,y,res->img["circle"],LH_TRANSITION_TIME,0.0,3.0,0xFFFF8080,0x00FF8080));
	if(lh_status==LH_TRANSITION_TIME && (!slow)) estg->add(new bubble(x,y,res->img["circle"],LH_TRANSITION_TIME,3.0,0.0,0x008080FF,0xFF8080FF));
	if(slow) lh_status++;
	else lh_status--;
	if(lh_status<0) lh_status=0;
	if(lh_status>LH_TRANSITION_TIME) lh_status=LH_TRANSITION_TIME;
	//
	//aura rotation
	aura1_rot+=AURA1_ROT_SPEED;
	aura2_rot+=AURA2_ROT_SPEED;
	//
	//fire
	current_cd--;
	if(estg->control.fire&&(current_cd<=0))
	{
		current_cd=cd;
		estg->play_se("se_plst00",0.2);
		fire();
	}
	//
	//bomb
	if(estg->control.bomb&&estg->data.spell>0)
	{
		if(dying_sts!=0)
		{
			card_get=false;
			bomb();
			dying_sts=0;
			estg->data.spell-=2;
			if(estg->data.spell<0)
				estg->data.spell=0;
		}
		else if(inv_sts==0)
		{
			card_get=false;
			bomb();
			estg->data.spell--;
		}
	}
	//
	//find target for bullets to aim
	find_tar();
	//
	//sts
	if(sts<-100.0) sts=-100.0;
	if(sts>+100.0) sts=+100.0;
	//inv
	if(inv_sts>0) inv_sts--;
	//
	//dying
	if(dying_sts>0) dying_sts--;
	if(dying_sts==1)
	{
		estg->data.player--;
		estg->data.spell=3;
		estg->add(new miss_protector());
	}
	//
	//graze graphic
	res->graze->ps->MoveTo(x2scr(real_x),y2scr(real_y),true);
	res->graze->ps->info.nEmission=(int)graze_freq;
	graze_freq=int(graze_freq*0.8);
	res->graze->ps->Update(0.0166667);
	res->graze->ps->Fire();
	//
}

void self_char::miss()
{
	if(inv_sts>0) return;
	estg->add(new bubble(real_x,real_y,res->img["orange_bubble"],16,0.0,6.0,0xFFFFFFFF,0x00FFFFFF));
	estg->add(new ge_ps(res->SPARK2[13],real_x,real_y,ENEMY_LAYER-1));
	estg->play_se("se_pldead00",0.3);
	inv(60);
	dying_sts=30;
	card_get=false;
}

void self_char::graze()
{
	estg->data.graze++;
	estg->data.score+=GRAZE_BONUS;
	if(!estg->self->slow)
	{
		estg->data.graze++;
		estg->data.score+=GRAZE_BONUS;
	}
	graze_freq=130.0;
	estg->play_se("se_graze",0.5);
}

void self_char::draw()
{
	//draw graze
	res->graze->ps->Render();
	//
	//draw char
	int i;
	if(slow) i=1;
	else i=0;
	int anm_counter=(age/8)%4;
	switch(lr_status)
	{
		case 5:
			f5[anm_counter][i]->SetFlip(true,false);
			f5[anm_counter][i]->Render(x2scr(real_x),y2scr(real_y));
			break;
		case 4:
			f4[i]->SetFlip(true,false);
			f4[i]->Render(x2scr(real_x),y2scr(real_y));
			break;
		case 3:
			f3[i]->SetFlip(true,false);
			f3[i]->Render(x2scr(real_x),y2scr(real_y));
			break;
		case 2:
			f2[i]->SetFlip(true,false);
			f2[i]->Render(x2scr(real_x),y2scr(real_y));
			break;
		case 1:
			f1[anm_counter][i]->SetFlip(true,false);
			f1[anm_counter][i]->Render(x2scr(real_x),y2scr(real_y));
			break;
		case -5:
			f5[anm_counter][i]->SetFlip(false,false);
			f5[anm_counter][i]->Render(x2scr(real_x),y2scr(real_y));
			break;
		case -4:
			f4[i]->SetFlip(false,false);
			f4[i]->Render(x2scr(real_x),y2scr(real_y));
			break;
		case -3:
			f3[i]->SetFlip(false,false);
			f3[i]->Render(x2scr(real_x),y2scr(real_y));
			break;
		case -2:
			f2[i]->SetFlip(false,false);
			f2[i]->Render(x2scr(real_x),y2scr(real_y));
			break;
		case -1:
			f1[anm_counter][i]->SetFlip(false,false);
			f1[anm_counter][i]->Render(x2scr(real_x),y2scr(real_y));
			break;
	}
	aura1_img->SetColor(((0x80*(LH_TRANSITION_TIME-lh_status)/LH_TRANSITION_TIME)<<24)+0xFFFFFF);
	aura2_img->SetColor(((0xFF*lh_status/LH_TRANSITION_TIME)<<24)+0xFFFFFF);
	aura1_img->RenderEx(x2scr(real_x),y2scr(real_y),aura1_rot);
	aura2_img->RenderEx(x2scr(real_x),y2scr(real_y),aura2_rot);
}

void self_char::find_tar()
{
	int i;
	float tar1_val,tar2_val,temp_val;
	list<bullet*>::iterator iter;
	list<bullet*>::iterator tar1;
	list<bullet*>::iterator tar2;
	bool find_1=false;
	bool find_2=false;
	tar1_val=-1e5;tar2_val=+1e5;
	for(i=0;i<MAX_LAYER;i++)
		for(iter=estg->blist[ENEMY][i].begin();iter!=estg->blist[ENEMY][i].end();iter++)
		{
			if((!(*iter)->suffer)||((*iter)->age<=0)) continue;
			temp_val=((*iter)->real_y-real_y)/(fabs((*iter)->real_x-real_x)+1e-5);
			if(temp_val>tar1_val)
			{
				tar1_val=temp_val;
				tar1=iter;
				find_1=true;
			}
			if(temp_val<tar2_val)
			{
				tar2_val=temp_val;
				tar2=iter;
				find_2=true;
			}
		}
	if(!find_1)
		sres.blt["tar1"]=0;
	else
		sres.blt["tar1"]=(void*)(*tar1);
	if(!find_2)
		sres.blt["tar2"]=0;
	else
		sres.blt["tar2"]=(void*)(*tar2);
}

void self_char::inv(int t)
{
	inv_sts=t;
}

miss_protector::miss_protector()
{
	clear_r=0;
	estg->self->inv(120);
}

void miss_protector::loop()
{
	int i;
	list<bullet*>::iterator iter;
	clear_r+=0.009;
	for(i=0;i<MAX_LAYER;i++)
		for(iter=estg->blist[ENEMY_BULLET][i].begin();iter!=estg->blist[ENEMY_BULLET][i].end();iter++)
			if((*iter)->age>0&&(*iter)->suffer&&is_collide(*iter,estg->self,clear_r))
				(*iter)->kill();
	if(age==180) destroy();
}

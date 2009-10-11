#include "ESTG.h"

#include <estg_math.h>
#include <iostream>
#include <common/common_res.h>
#include <common/item/item.h>

using namespace std;

ESTG* estg=0;
HGE* hge=0;
cres* res=0;

ESTG::ESTG()
{
	self=0;
	stage_master=0;
	res=new cres();
	pause=false;
	xorg=(RESOLUTION_Y*5/12.0);
	yorg=(RESOLUTION_Y/2.0);
	xstr=(RESOLUTION_Y*5/6.0);
	ystr=(-RESOLUTION_Y*5/6.0);
	xos=yos=0.0;
	shake_status=0;
	bg1=bg2=0;
	bg_trans_time=60;
	bg_trans_status=0;
	se_volume=1.0;
	bgm_volume=1.0;
	bgm.next_bgm=0;
	bgm.bgm_chn=0;
	bgm.fade_status=0;
}

inline void ESTG::add_self(int _self)
{
	pause=false;
	switch(_self)
	{
		case GREEN_DAM:
		{
			self=(self_char*)(*(estg->add(new green_dam())));
			break;
		}
		default:
			exit(0);
	}
}

void ESTG::reset(int _self)
{
	ticker=0;
	add_self(_self);
}

void ESTG::set_bg(back_ground* pbg,int trans_time)
{
	if(trans_time==0) trans_time=60;
	bg_trans_time=bg_trans_status=trans_time;
	if(bg1==0&&bg2==0)
	{
		bg1=(back_ground*)(*(estg->add(pbg)));
		return;
	}
	if(bg1!=0&&bg2==0)
	{
		bg2=(back_ground*)(*(estg->add(pbg)));
		return;
	}
	if(bg1!=0&&bg2!=0)
	{
		bg1->dead=true;
		bg1=bg2;
		bg2=(back_ground*)(*(estg->add(pbg)));
		return;
	}
}

ESTG::~ESTG(){}



list<bullet*>::iterator ESTG::add(bullet* pbullet)
{
	blist[pbullet->attr][pbullet->layer].push_front(pbullet);
	return pbullet->it=blist[pbullet->attr][pbullet->layer].begin();
}

void ESTG::loop()
{
	//bgm
	if(bgm.fade_status==1)
	{
		if(bgm.bgm_chn!=0) hge->Channel_Stop(bgm.bgm_chn);
		bgm.bgm_chn=hge->Effect_PlayEx(bgm.next_bgm,(int)(100*bgm_volume));
		hge->Channel_SetPos(bgm.bgm_chn,0.1);
	}
	if(bgm.fade_status>0)
		bgm.fade_status--;
	bgm.pos=hge->Channel_GetPos(bgm.bgm_chn);
	if(bgm.pos>bgm.loop_end)
		hge->Channel_SetPos(bgm.bgm_chn,bgm.pos-bgm.loop_lenth);
	//pause
	if(pause) return;
	//run estg system
	ticker++;
	run_scripts();
	//??

	//backgroud
	if(bg_trans_status>0) bg_trans_status--;
	//shake
	if(shake_status>0)
	{
		shake_status--;
		xos=5*sin(float(shake_status*shake_status));
		yos=5*sin(float(shake_status*(shake_status+3)));
	}
	//
}

void ESTG::shake(int duration)
{
	shake_status=duration;
}

void ESTG::run_scripts()//in fact, they are NOT scripts.
{
	list<bullet*>::iterator iter,iter2;
	int i,j,k;
	//delete dead bullets.
	for(i=0;i<MAX_ATTR;i++)
		for(j=0;j<MAX_LAYER;j++)
			for(iter=blist[i][j].begin();iter!=blist[i][j].end();)
			{
				if((*iter)->dead)
				{
					delete (*iter);
					iter=blist[i][j].erase(iter);
					continue;
				}
				iter++;
			}
	//age++
	for(i=0;i<MAX_ATTR;i++)
		for(j=0;j<MAX_LAYER;j++)
			for(iter=blist[i][j].begin();iter!=blist[i][j].end();iter++)
				(*iter)->age++;
	//
	//run scripts of all bullets
	for(i=0;i<MAX_ATTR;i++)
		for(j=0;j<MAX_LAYER;j++)
			for(iter=blist[i][j].begin();iter!=blist[i][j].end();iter++)
				if((*iter)->age>0)
					(*iter)->loop();
	//update real (x,y)
	for(i=0;i<MAX_ATTR;i++)
		for(j=0;j<MAX_LAYER;j++)
			for(iter=blist[i][j].begin();iter!=blist[i][j].end();iter++)
				(*iter)->update_xy();
	//update particle systems
	for(i=0;i<MAX_ATTR;i++)
		for(j=0;j<MAX_LAYER;j++)
			for(iter=blist[i][j].begin();iter!=blist[i][j].end();iter++)
				if((*iter)->ps!=0)
				{
					(*iter)->ps->MoveTo(x2scr((*iter)->real_x),y2scr((*iter)->real_y));
					(*iter)->ps->Update(0.0166667);
				}
	//collide of ENEMY_BULLET and SELF_CHAR
	for(j=0;j<MAX_LAYER;j++)
		for(iter=blist[ENEMY_BULLET][j].begin();iter!=blist[ENEMY_BULLET][j].end();iter++)
			if(is_collide(*iter,self)) (*iter)->collide(self);
	//
	//collide of SELF_BULLET and ENEMY
	for(j=0;j<MAX_LAYER;j++)
		for(k=0;k<MAX_LAYER;k++)
			for(iter=blist[ENEMY][j].begin();iter!=blist[ENEMY][j].end();iter++)
				for(iter2=blist[SELF_BULLET][k].begin();iter2!=blist[SELF_BULLET][k].end();iter2++)
					if(is_collide(*iter2,*iter)) (*iter2)->collide(*iter);
	//
	//automatically clear bullets that are out of screen
	if(ticker%16==0)
		for(i=0;i<MAX_ATTR;i++)
			for(j=0;j<MAX_LAYER;j++)
				for(iter=blist[i][j].begin();iter!=blist[i][j].end();iter++)
					if((*iter)->age>=0)
						if((*iter)->auto_clear)
							if(fabs((*iter)->real_x)>OUTER_PLAY_AREA_X||fabs((*iter)->real_y)>OUTER_PLAY_AREA_Y)
								(*iter)->destroy();
	//update minions' master's status
	for(i=0;i<MAX_ATTR;i++)
		for(j=0;j<MAX_LAYER;j++)
			for(iter=blist[i][j].begin();iter!=blist[i][j].end();iter++)
				if((*iter)->master!=0&&(*iter)->master!=(bullet*)(1))
					if((*iter)->master->dead)
						if((*iter)->master->hp>0)
							(*iter)->master=0;//master was destroyed
						else
							(*iter)->master=(bullet*)(1);//master was killed
	//play sound effect
	map<char*,estg_se*,charcmp>::iterator snd_it;
	for(snd_it=res->snd.begin();snd_it!=res->snd.end();snd_it++)
	{
		if(snd_it->second->vol>0.01)
		{
			if(hge->Channel_IsPlaying(snd_it->second->ch))
				hge->Channel_SetPos(snd_it->second->ch,0);
			else
				snd_it->second->ch=hge->Effect_PlayEx(snd_it->second->se,int(100*se_volume*log(snd_it->second->vol)/SND_FACTOR));
		}
		snd_it->second->vol=0;
	}
}

void ESTG::play_bgm(HEFFECT se_bgm,float lp_end,float lp_lenth)
{
	bgm.fade_status=120;
	bgm.next_bgm=se_bgm;
	bgm.loop_end=lp_end;
	bgm.loop_lenth=lp_lenth;
	if(bgm.bgm_chn!=0) hge->Channel_SlideTo(bgm.bgm_chn,1.5,0);
}

void ESTG::destroy_all_enemy()
{
	int i,j;
	list<bullet*>::iterator iter;
	for(i=0;i<MAX_ATTR;i++)
			for(j=0;j<MAX_LAYER;j++)
				for(iter=blist[i][j].begin();iter!=blist[i][j].end();iter++)
					if((*iter)->hostile)
					{
						estg->add(new bullet_corpse(*iter));
						(*iter)->destroy();
					}
}

void ESTG::kill_all_bullet()
{
	int j;
	list<bullet*>::iterator iter;
		for(j=0;j<MAX_LAYER;j++)
			for(iter=blist[ENEMY_BULLET][j].begin();iter!=blist[ENEMY_BULLET][j].end();iter++)
				if((*iter)->age>0&&(*iter)->suffer)
					(*iter)->kill();
}

inline bool is_collide(bullet* attacker,bullet* sufferer,float sufferer_r)
{
	if(!(attacker->attack&&sufferer->suffer)) return false;
	if(attacker->age<=0||sufferer->age<=0) return false;
	if(sufferer_r<0) sufferer_r=sufferer->img->a;
	float dx,dy,x,y,rot,a2,b2,l;
	dx=sufferer->real_x-attacker->real_x;
	dy=sufferer->real_y-attacker->real_y;
	l=sufferer_r*1.5+attacker->img->r;
	if(dx>l||dx<-l||dy>l||dy<-l) return false;
	rot=M_PI_2*(attacker->rot+attacker->crot);
	x= dx*cos(rot)+dy*sin(rot);
	y=-dx*sin(rot)+dy*cos(rot);
	a2=attacker->img->a+sufferer_r;
	b2=attacker->img->b+sufferer_r;
	a2=a2*a2;b2=b2*b2;
	x=x*x;y=y*y;
	if(attacker->img->rect)return (x<b2 && y<a2);
	else return ((x*a2+y*b2)<a2*b2);
}

#include "stage_marisa_enemy.h"
#include <common\bullet\sector.h>
#include <common\bullet\str2ran.h>
#include <common\bullet\acc_str_bullet.h>
#include <common\bullet\grav_bullet.h>

//--wave0--//
stage_marisa_wave_0::stage_marisa_wave_0(float xf,float yf,int stay,int fly_in,int fly_out)
{
	drop_num=3;
	cx=xf;cy=yf;
	_stay=stay;
	in_mode=fly_in;
	out_mode=fly_out;
}

void stage_marisa_wave_0::loop()
{
	if(fabs(real_x)>0.54||fabs(real_y)>0.64)
		suffer=false;
	else
		suffer=true;
	if(age<90)
	{
		if(in_mode==0)
		{
			x=0.0;
			y=(90-age)*(90-age)/12000.0;
		}
		else
		{
			if(cx>0)
			{
				y=0.0;
				x=(90-age)*(90-age)/12000.0;
			}
			else
			{
				y=0.0;
				x=-(90-age)*(90-age)/12000.0;
			}
		}
	}
	if(age==90+_stay) dmg_factor=2.0;
	if(age>90+_stay)
	{
		if(out_mode==0)
		{
			x=0.0;
			y=(age-90-_stay)*(age-90-_stay)/12000.0;
		}
		else
		{
			if(cx>0)
			{
				y=0.0;
				x=(age-90-_stay)*(age-90-_stay)/12000.0;
			}
			else
			{
				y=0.0;
				x=-(age-90-_stay)*(age-90-_stay)/12000.0;
			}
		}
	}
	if(age>180+_stay) destroy();
}
//--end of wave0--//

//--wave1--//
stage_marisa_wave_1::stage_marisa_wave_1(int delay,float fire_pos,int direction):girl(1)
{
	hp=9;
	age=-delay;
	dir=direction;
	_fire_pos=fire_pos;
	fired=fired2=false;
	dmg_factor=0.5;
}

void stage_marisa_wave_1::loop()
{
	y=0.64-age*0.005;
	x=atan(y*6.0-1.0)*0.3*dir;
	if((!fired)&&y<_fire_pos)
	{
		estg->add(new sector<>(real_x,real_y,0.0,0.5,res->BALL1[2],true,7,3,0.08,0,+dir*0.02,0.08));
		estg->play_se("se_tan00",0.1);
		fired=true;
		dmg_factor=0.7;
	}
	if((!fired2)&&y<(_fire_pos-0.3)) 
	{
		estg->add(new sector<>(real_x,real_y,0.0,0.5,res->BALL1[2],true,7,3,0.08,0,-dir*0.02,0.08));
		estg->play_se("se_tan00",0.1);
		fired2=true;
		dmg_factor=1.0;
	}
	if(y<-0.64) destroy();
}
//--end of wave1--//

//--wave2--//
stage_marisa_wave_2::stage_marisa_wave_2(int delay,int fire_time,int direction):girl(3)
{
	hp=15;
	age=-delay;
	dir=direction;
	_fire_time=fire_time;
	fires=900;
	dmg_factor=0.5;
}

void stage_marisa_wave_2::loop()
{
	x=(0.54-age*0.003)*dir;
	y=0.3+0.1*sin(x*10.0);
	if((fires>0)&&(age>_fire_time))
	{
		fires--;
		if(fires%40==0)
			estg->add(new sector<>(real_x,real_y,1000,0.4,res->BARROW[hge->Random_Int(0,15)],true,10,1,0.4,0,0,0.05,ENEMY_BULLET_LAYER+1));
		if(fires%10==0)
		{
			estg->add(new sector<>(real_x,real_y,0.0,0.8,res->BALL0[13],true,5,1,0.8,0,0,0.05));
			estg->play_se("se_tan00",0.1);
		}
		if(fires==800)
			dmg_factor=1.0;
	}
	if(x*dir<-0.54) destroy();
}
//--end of wave2--//

//--wave3--//
stage_marisa_wave_3_minion::stage_marisa_wave_3_minion(bullet* master,int type,float start_angle)
:satellite_ghost(master,start_angle,0.07,4.74)
{
	if(type!=0)
	{
		x*=2.0;
		_av*=-0.5;
	}
	_type=type;
}

void stage_marisa_wave_3_minion::loop()
{
	satellite_ghost::loop();
	if(age%15==5 && age>60)
		if(_type!=0)
		{
			estg->add(new straight_bullet(real_x,real_y,crot+0.5+age/144.0,0.3,res->BALL1[10]));
			estg->add(new straight_bullet(real_x,real_y,crot+0.6+age/144.0,0.3,res->BALL1[10]));
				
		}
		else
		{
			estg->add(new straight_bullet(real_x,real_y,crot-0.0,0.23,res->BALL1[0]));
			estg->add(new straight_bullet(real_x,real_y,crot-0.05,0.2,res->BALL1[0]));
			estg->add(new straight_bullet(real_x,real_y,crot-0.54,0.23,res->BALL1[0]));
			estg->add(new straight_bullet(real_x,real_y,crot-0.55,0.2,res->BALL1[0]));
			estg->add(new sector<str2ran>(real_x,real_y,0.0,0.3,res->SRICE[2],true,3,1,0.4,0,0,0,20,0,0));
		}
}

stage_marisa_wave_3::stage_marisa_wave_3(float xf,float yf):stage_marisa_wave_0(xf,yf,600)
{
	_aura=true;
	hp=90;
	dmg_factor=0.0;
	drop_num=6;
}

void stage_marisa_wave_3::loop()
{
	stage_marisa_wave_0::loop();
	if(age==1)
	{
		int i;
		float angle_os=hge->Random_Float(0,4.0);
		for(i=0;i<6;i++)
			estg->add(new stage_marisa_wave_3_minion(this,1,angle_os+i*4.0/6.0));
		for(i=0;i<3;i++)
			estg->add(new stage_marisa_wave_3_minion(this,0,angle_os+i*4.0/3.0));
	}
	if(age==60)
		dmg_factor=1.0;
	if(age>60&&age<720&&age%15==2)
		estg->play_se("se_tan00",0.1);
}

stage_marisa_wave_4_bullet::stage_marisa_wave_4_bullet(float x0,float y0,float angle,float v0,float v1,float t0,pic* image)
{
	cx=x0;cy=y0;crot=angle;
	_v0=v0/60.0;_v1=v1/60.0;_t0=t0*60.0;
	img=image;
	drop_num=3;
}

void stage_marisa_wave_4_bullet::loop()
{
	x=_v0*age+(_v1-_v0)*_t0*(1-exp(-age/_t0));
}

stage_marisa_wave_4::stage_marisa_wave_4(float xf,float yf):stage_marisa_wave_0(xf,yf,480)
{
	_aura=true;
	_type=9;
	rot=hge->Random_Float(0,4.0);
	hp=30;
}

void stage_marisa_wave_4::loop()
{
	stage_marisa_wave_0::loop();
	if(age>60&&age<300&&age%2==1)
	{
		estg->add(new stage_marisa_wave_4_bullet(real_x,real_y,hge->Random_Float(0,4),0.15,1.0,0.5,res->BALL1[0]));
		estg->add(new stage_marisa_wave_4_bullet(real_x,real_y,hge->Random_Float(0,4),0.2,1.3,0.5,res->BALL1[10]));
	}
	if(age>60&&age<300&&age%7==1) estg->play_se("se_tan00",0.1);
	if(age==300) dmg_factor=2.0;
}

stage_marisa_wave_5_minion::stage_marisa_wave_5_minion(bullet* master,float start_angle):satellite_ghost(master,start_angle,0.15,2.34)
{
	
}

void stage_marisa_wave_5_minion::loop()
{
	satellite_ghost::loop();
	if(age>60&&age%60==30&&(!dead))
	{
		float a=v2a(master->real_x+estg->self->real_x-2*real_x,master->real_y+estg->self->real_y-2*real_y);
		estg->add(new sector<>(real_x,real_y,a,0.3,res->BARROW[12],false,6,4,0.3,0,0,0,6,0,4));
	}
}

stage_marisa_wave_5::stage_marisa_wave_5(float x0):stage_marisa_wave_0(x0,0.35,600)
{
	_type=10;
	_aura=true;
	x=x0;
	hp=180;
	drop_num=8;
}

void stage_marisa_wave_5::loop()
{
	int i;
	stage_marisa_wave_0::loop();
	if(age==1)
		for(i=0;i<5;i++)
			estg->add(new stage_marisa_wave_5_minion(this,0.8*i));
	if(age>60&&age<720)
	{
		if(age%60==30)
		{
			estg->play_se("se_tan00",0.15);
			estg->add(new sector<>(real_x,real_y,0,0.4,res->BALL1[2],false,64,1,0.0625,0,0,0));
		}
	}
	if(age==660) dmg_factor=2.0; 
}

stage_marisa_wave_6::stage_marisa_wave_6(int type,int index)
{
	hp=15;
	_type=type;
	_index=index;
	age=_index*20-80;
}

void stage_marisa_wave_6::loop()
{
	int i;
	y=0.48-_index*0.06+0.02*sin(age/20.0);
	if(age<-_index*3+36) x=(0.54-age*0.005)*_type;
	if(age==480-_index*80+_type*30)
	{
		x=0;
		cx=real_x;
		for(i=0;i<40;i++)
			estg->add(new straight_bullet(real_x,real_y,hge->Random_Float(-0.7,0.7),hge->Random_Float(0.2,0.4),res->SRICE[0],true));
		estg->play_se("se_tan00",0.1);
	}
	if(age>840+_index*40)
		x=_type*(age-840-_index*40)*0.005;
	if(age>840&&fabs(real_x)>0.54) destroy();
}

stage_marisa_wave_8::stage_marisa_wave_8(float xf,float yf,int stay):stage_marisa_wave_0(xf,yf,stay,1,1)
{
	hp=60;
	_type=8;
	_aura=true;
}

void stage_marisa_wave_8::loop()
{
	stage_marisa_wave_0::loop();
	if(age>90&&age<90+_stay&&age%49==0)
	{
		estg->add(new sector<>(real_x,real_y,age/600.0,0.3,res->SRICE[12],false,16,3,0.25,0,0,0.05));
		estg->play_se("se_tan00",0.15);
	}
}

stage_marisa_wave_9::stage_marisa_wave_9(float xf,float yf,int stay):stage_marisa_wave_0(xf,yf,stay,0,0)
{
	hp=45;
	_type=9;
	_aura=true;
}

void stage_marisa_wave_9::loop()
{
	stage_marisa_wave_0::loop();
	if(age>90&&age<90+_stay&&age%53==13)
	{
		estg->add(new sector<>(real_x,real_y,-1.0,0.4,res->BALL1[5],false,3,5,0.2,0,0,0.04));
		estg->play_se("se_tan00",0.15);
	}
}

stage_marisa_wave_10::stage_marisa_wave_10(float xf,float yf,int stay):stage_marisa_wave_0(xf,yf,stay,0,1)
{
	hp=45;
	_type=10;
	_aura=true;
}

void stage_marisa_wave_10::loop()
{
	int i;
	stage_marisa_wave_0::loop();
	if(age>90&&age<90+_stay&&age%83==34)
	{
		for(i=0;i<20;i++)
			estg->add(new straight_bullet(real_x,real_y,hge->Random_Float(-0.3,0.3),hge->Random_Float(0.2,0.4),res->SARROW[2],true));
		estg->play_se("se_tan00",0.15);
	}
}

stage_marisa_wave_11::stage_marisa_wave_11(float xf,float yf,int stay):stage_marisa_wave_0(xf,yf,stay,0,1)
{
	hp=30;
	_type=11;
	_aura=true;
}

void stage_marisa_wave_11::loop()
{
	stage_marisa_wave_0::loop();
	if(age>90&&age<90+_stay&&age%97==22)
	{
		estg->add(new sector<>(real_x,real_y,0,0.3,res->SARROW[6],true,64,1,0.0625,0,0,0));
		estg->play_se("se_tan00",0.15);
	}
}

stage_marisa_wave_12::stage_marisa_wave_12(int dir)
{
	_dir=dir;
}

void stage_marisa_wave_12::loop()
{
	if(age<40)
	{
		x=0.3*_dir;
		y=0.64-age*0.006;
	}
	if(age>=40&&age<190)
	{
		x=_dir*0.3*cos((age-40)/150.0*M_PI);
		y=0.4-0.3*sin((age-40)/150.0*M_PI);
	}	
	if(age>=190)
	{
		x=-0.3*_dir;
		y=0.4-(190-age)*0.006;
	}
	if(age==230) destroy();
}

stage_marisa_wave_13::stage_marisa_wave_13(int dir,int fire):stage_marisa_wave_12(dir)
{
	hp=15;
	_type=1;
	_fire=fire;
}

void stage_marisa_wave_13::loop()
{
	stage_marisa_wave_12::loop();
	if(age%120==_fire)
		estg->add(new sector<>(real_x,real_y,0,0.4,res->BALL0[4],true,3,2,0.1,0,0,0.06));
}

stage_marisa_wave_14::stage_marisa_wave_14(float xf,float yf,int stay):stage_marisa_wave_0(xf,yf,stay,0,1)
{
	hp=30;
	_type=12;
	_aura=true;
}

void stage_marisa_wave_14::loop()
{
	int i;
	float agl,v0;
	stage_marisa_wave_0::loop();
	if(suffer&&age%77==34)
	{
		for(i=0;i<10;i++)
		{
			agl=hge->Random_Float(M_PI_2-0.7,M_PI_2+0.7);
			v0=hge->Random_Float(0.2,0.4);
			estg->add(new grav_bullet(real_x,real_y,v0*cos(agl),v0*sin(agl),res->BALL1[2]));
		}
		estg->play_se("se_tan00",0.15);
	}
}

stage_marisa_wave_15_minion::stage_marisa_wave_15_minion(bullet* master,float start_angle,float r,float av)
:satellite_ghost(master,start_angle,r,av)
{
	
}

void stage_marisa_wave_15_minion::loop()
{
	satellite_ghost::loop();
	if(age>90&&age<1200)
	{
		if(x<0.2&&age%8==1)
			estg->add(new sector<>(real_x,real_y,crot,0.4,res->SRICE[0],false,3,1,0.45,0,0,0));
		if(x>0.2&&age%30==1)
			estg->add(new sector<>(real_x,real_y,crot,0.2,res->SRICE[2],false,3,1,0.3,0,0,0));
	}
}

stage_marisa_wave_15::stage_marisa_wave_15(float x0):stage_marisa_wave_0(x0,0.2,900)
{
	_type=10;
	_aura=true;
	x=x0;
	hp=450;
	drop_num=16;
}

void stage_marisa_wave_15::loop()
{
	int i;
	stage_marisa_wave_0::loop();
	if(age==1)
	{
		for(i=0;i<5;i++)
			estg->add(new stage_marisa_wave_15_minion(this,0.8*i,0.15,+2.34));
		for(i=0;i<10;i++)
			estg->add(new stage_marisa_wave_15_minion(this,0.4*i,0.30,-1.17));
	}
	if(age>90&&age<900)
	{
		if(age%24==12)
		{
			estg->add(new sector<>(real_x,real_y,0,0.4,res->BARROW[6],true,5,7,0.8,0,0,0,8,0,4));
			estg->play_se("se_tan00",0.15);
		}
		if(age%5==0)
			estg->play_se("se_tan00",0.1);
	}
}

test_laser::test_laser():laser(4)
{
	node=1.0;
	has_aura=true;
}

void test_laser::loop()
{
	laser::loop();
	rot+=0.01;
	if(age%120==10) turn_on();
	if(age%120==70) turn_off();
}

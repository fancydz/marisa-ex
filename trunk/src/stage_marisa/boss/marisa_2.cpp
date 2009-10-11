#include "marisa_2.h"
#include "marisa_1.h"
#include <ESTG.h>
#include <common\bullet\sector.h>
#include <common\bullet\circle.h>
#include <common\bullet\straight_bullet.h>
#include <common\ge\bubble.h>
#include "cannon.h"
#include "..\\marisa_bg.h"

marisa_2::marisa_2(float x0,float y0):marisa(x0,y0)
{
	age=-1;
	estg->destroy_all_enemy();
}

void marisa_2::loop()
{
	if(age>=0       && age<  SC_OS)
		nm_1(age);

	if(age>=SC_OS   && age<2*SC_OS)
		sc_1(age-1*SC_OS);

	if(age>=SC_OS*2 && age<3*SC_OS)
		nm_2(age-2*SC_OS);

	if(age>=SC_OS*3 && age<4*SC_OS)
		sc_2(age-3*SC_OS);

	if(age>=SC_OS*4 && age<5*SC_OS)
		nm_3(age-4*SC_OS);

	if(age>=SC_OS*5 && age<6*SC_OS)
		sc_3(age-5*SC_OS);

	if(age>=SC_OS*6 && age<7*SC_OS)
		nm_4(age-6*SC_OS);

	if(age>=SC_OS*7 && age<8*SC_OS)
		sc_4(age-7*SC_OS);

	if(age>=SC_OS*8 && age<9*SC_OS)
		nm_5(age-8*SC_OS);

	if(age>=SC_OS*9 && age<10*SC_OS)
		sc_5(age-9*SC_OS);

	if(age>=SC_OS*10 && age<11*SC_OS)
		nm_6(age-10*SC_OS);

	if(age>=SC_OS*11 && age<12*SC_OS)
		sc_6(age-11*SC_OS);

	if(age>=SC_OS*12 && age<13*SC_OS)
		nm_7(age-12*SC_OS);

	if(age>=SC_OS*13 && age<14*SC_OS)
		sc_7(age-13*SC_OS);

	if(age>=SC_OS*14 && age<15*SC_OS)
		nm_8(age-14*SC_OS);

	if(age>=SC_OS*15 && age<16*SC_OS)
		sc_8(age-15*SC_OS);

	if(age>=SC_OS*16 && age<17*SC_OS)
		nm_9(age-16*SC_OS);

	if(age>=SC_OS*17 && age<18*SC_OS)
		sc_9(age-17*SC_OS);

	if(age>=SC_OS*18 && age<19*SC_OS)
		sc_10(age-18*SC_OS);

	if(age>=SC_OS*19 && age<20*SC_OS)
		escape(age-19*SC_OS);

	boss::loop();
}

void marisa_2::sc_1(int t)
{
	int i;
	if(t==1)
	{
		estg->set_bg(new marisa_bg());
		hp=1500;
		move_to(0,0.3);
	}
	if(t==90)
		for(i=0;i<64;i++)
			estg->add(new marisa_2_1_laser(i));
	if(t>60)
	{
		if(t%120==1)
		{
			estg->add(new sector<>(real_x,real_y,0,0.12,res->SSTAR[13],false,80,1,0.05,0,0,0,0,0,0,-2,0,0));
			estg->play_se("se_tan00",0.15);
		}
		if(t%120==51)
		{
			estg->add(new sector<>(real_x,real_y,0.025,0.12,res->SSTAR[13],false,80,1,0.05,0,0,0,0,0,0,2,0,0));
			estg->play_se("se_tan00",0.15);
		}
	}
}

void marisa_2::sc_2(int t)
{
	int i;
	if(t==1)
	{
		estg->set_bg(new marisa_bg());
		hp=1250;
		move_to(0,0.3);
	}
	if(t==90)
		for(i=0;i<5;i++)
			estg->add(new marisa_2_2_minion(this,i));
	if(t%150==120)
	{
		if(t==120) (*estg->add(new marisa_2_2_laser(real_x,real_y)))->attack=false;
		else estg->add(new marisa_2_2_laser(real_x,real_y));
	}
	if(t>75)
	{
		if(real_x>(estg->self->real_x+0.01)) x2-=0.0035;
		if(real_x<(estg->self->real_x-0.01)) x2+=0.0035;
	}
}

void marisa_2::sc_3(int t)
{
	int i;
	if(t==1)
	{
		estg->set_bg(new marisa_bg());
		hp=1000;
		move_to(0.0,0.3);
	}
	if(t==120)
		for(i=0;i<5;i++)
			estg->add(new marisa_2_3_minion(this,i));
	if(t%720==60)
		for(i=13;i<35;i++)
			(*estg->add(new marisa_2_3_laser(1.4,1.0,-1-i*0.025,0)))->age=i*3-120;
	if(t%720==420)
		for(i=13;i<35;i++)
			(*estg->add(new marisa_2_3_laser(-1.4,1.0,-1+i*0.025,6)))->age=i*3-120;
	if(t>60)
	{
		x2=sin(t*0.01)*0.03;
		y2=0.3+sin(t*0.003)*0.1;
	}
}

void marisa_2::sc_4(int t)
{
	int i,j,rot0;
	if(t==1)
	{
		estg->set_bg(new marisa_bg());
		hp=1500;
		move_to(0,0);
	}
	if(t>=60&&t<=135&&t%15==0)
	{
		estg->play_se("se_option",0.3);
		(*estg->add(new marisa_2_4_laser(t/15-4)))->age=t+180;
		(*estg->add(new marisa_2_4_laser(15-t/15)))->age=t+180;
	}
	if(t%720==600)
	{
		estg->play_se("se_tan00",0.2);
		for(i=1;i<7;i++)
		{
			rot0=hge->Random_Float(0,4);
			for(j=0;j<(i*10+20);j++)
				estg->add(new marisa_2_4_star(rot0+float(j)/(i*10+20)*4,0.0016+0.0008*i));
		}
	}
	if(t%720==120&&t>720)
		estg->play_se("se_kira00",0.4);
}

void marisa_2::sc_5(int t)
{
	if(t==1)
	{
		estg->set_bg(new marisa_bg());
		hp=750;
	}
	if(t%480==  1) move_to(0.0,0.3);
	if(t%480==121) move_to(0.15,0.35);
	if(t%480==241) move_to(0.0,0.3);
	if(t%480==361) move_to(-0.15,0.35);
	if(t==60) estg->add(new marisa_2_5_comet());
	if(t>60&&t%30==10)
	{
		estg->add(new sector<>(real_x,real_y,age*0.002083,0.2,res->SSTAR[6],false,32,1,0.125,0,0,0,0,0,0,2,0,0));
		estg->play_se("se_tan00",0.15);
	}
}

void marisa_2::sc_6(int t)
{
	static float dis=0.0;
	static float last_x,last_y;
	if(t==30) estg->sres.val["sc6"]=0.0;
	float xx,yy;
	if(t>60)
	{
		xx=last_x-estg->self->real_x;
		yy=last_y-estg->self->real_y;
		dis+=sqrt(xx*xx+yy*yy);
		if(dis>0.05)
		{
			estg->add(new marisa_2_6_bullet(int(estg->sres.val["sc6"]+0.5),estg->self->x,estg->self->y));
			dis=0;
			estg->sres.val["sc6"]=estg->sres.val["sc6"]+1.0;
		}
	}
	last_x=estg->self->real_x;
	last_y=estg->self->real_y;
	if(t==1)
	{
		estg->set_bg(new marisa_bg());
		hp=1250;
	}
	if(t%480==  1) move_to(0.0,0.4);
	if(t%480==121) move_to(0.1,0.45);
	if(t%480==241) move_to(0.0,0.4);
	if(t%480==361) move_to(-0.1,0.45);
	if(t>60&&t%60==10)
	{
		estg->play_se("se_tan00",0.15);
		estg->add(new sector<>(real_x,real_y,0,0.2,res->BSTAR[1],true,25,1,0.16,0,0,0,0,0,0,-2,0,0));
	}
}

void marisa_2::sc_7(int t)
{
	int i;
	if(t==1)
	{
		estg->set_bg(new marisa_bg());
		move_to(0,0);
		hp=750;
	}
	if(t%750==90)
		for(i=0;i<5;i++)
			estg->add(new marisa_2_7_laser(i));
	if(t>60&&t%60==10)
	{
		estg->play_se("se_tan00",0.15);
		estg->add(new sector<marisa_2_7_bullet>(real_x,real_y,t*0.003,0.15,res->SSTAR[2],false,6,5,0.6667,0,0,0.03,0,0,0,0,0,+0.1));
	}
	if(t>60&&t%60==40)
	{
		estg->play_se("se_tan00",0.15);
		estg->add(new sector<marisa_2_7_bullet>(real_x,real_y,t*0.003,0.15,res->SSTAR[2],false,6,5,0.6667,0,0,0.03,0,0,0,0,0,-0.1));
	}
	
}

void marisa_2::sc_8(int t)
{
	int i;
	if(t==1)
	{
		estg->set_bg(new marisa_bg());
		move_to(0,0.2);
		hp=750;
	}
	if(t>60&&t%3==1)
		if(t%180<30)
		{
			estg->play_se("se_tan00",0.15);
			for(i=0;i<25;i++)
				estg->add(new marisa_2_8_bullet(real_x,real_y,+t*0.0033+i*0.16,0.2,res->BARROW[12],t%180,i));
		}
		else if(t%180>90&&t%180<=120)
		{
			estg->play_se("se_tan00",0.15);
			for(i=0;i<25;i++)
				estg->add(new marisa_2_8_bullet(real_x,real_y,-t*0.0033+i*0.16,0.2,res->BARROW[12],t%180,i));
		}
}

void marisa_2::sc_9(int t)
{
	static float rot0=0;
	if(t==1)
	{
		estg->set_bg(new marisa_bg());
		hp=750;
	}
	if(t==60)
	{
		estg->add(new marisa_2_9_minion(+0.43,0.53));
		estg->add(new marisa_2_9_minion(-0.43,0.53));
	}
	if(t%480==  1) move_to(0.0,0.4);
	if(t%480==121) move_to(0.2,0.45);
	if(t%480==241) move_to(0.0,0.4);
	if(t%480==361) move_to(-0.2,0.45);
	if(t>60)
	{
		estg->play_se("se_tan00",0.1);
		float v=hge->Random_Float(0.13,0.3);
		estg->add(new sector<>(real_x,real_y,(2*(t%2)-1)*t*0.067+hge->Random_Float(0.9,1.1),v,res->BARROW[hge->Random_Int(0,15)],false,1,7,0,0,0,v*0.015,0,0,0));
	}
}

void marisa_2::sc_10(int t)
{
	if(t==1)
	{
		estg->set_bg(new marisa_bg());
		hp=750;
	}
	if(t%480==  1) move_to(-0.2,0.45);
	if(t%480==121) move_to(0.4,0.25);
	if(t%480==241) move_to(+0.2,0.45);
	if(t%480==361) move_to(-0.4,0.25);
	if(t>60&&t%20==5)
	{
		estg->play_se("se_tan00",0.15);
		estg->add(new marisa_2_10_bullet(real_x,real_y,0.5+hge->Random_Float(0,1),hge->Random_Float(0.4,0.6),res->img["comet_fast"]));
		estg->add(new marisa_2_10_bullet(real_x,real_y,1.5+hge->Random_Float(0,1),hge->Random_Float(0.4,0.6),res->img["comet_fast"]));
		estg->add(new marisa_2_10_bullet(real_x,real_y,2.5+hge->Random_Float(0,1),hge->Random_Float(0.4,0.6),res->img["comet_fast"]));
		estg->add(new marisa_2_10_bullet(real_x,real_y,3.5+hge->Random_Float(0,1),hge->Random_Float(0.4,0.6),res->img["comet_fast"]));
	}
	if(t>60&&t%3!=0)
	{
		estg->add(new marisa_2_10_bullet(real_x,real_y,t*0.05+hge->Random_Float(0,0.5),hge->Random_Float(0.1,0.3),res->SSTAR[6]));
		estg->add(new marisa_2_10_bullet(real_x,real_y,t*0.05+hge->Random_Float(0,0.5),hge->Random_Float(0.1,0.3),res->SSTAR[10]));
	}
}

void marisa_2::nm_1(int t)
{
	if(t==1)
	{
		hp=750;
	}
	if(t%960==  1) move_to(0.0,0.35);
	if(t%960==241) move_to(0.2,0.3);
	if(t%960==481) move_to(0.0,0.35);
	if(t%960==721) move_to(-0.2,0.3);
	if(t>180&&t%60==1)
	{
		estg->play_se("se_tan00",0.15);
		estg->add(new sector<>(real_x,real_y,t*0.12345+0.01,0.20,res->BARROW[0],false,50,1,0.08,0,0,0));
		estg->add(new sector<>(real_x,real_y,t*0.12345+0.03,0.24,res->BARROW[4],false,50,1,0.08,0,0,0));
		estg->add(new sector<>(real_x,real_y,t*0.12345+0.05,0.28,res->BARROW[8],false,50,1,0.08,0,0,0));
		estg->add(new sector<>(real_x,real_y,t*0.12345+0.07,0.32,res->BARROW[12],false,50,1,0.08,0,0,0));
	}
}

void marisa_2::nm_2(int t)
{
	int i,k;
	if(t==1)
	{
		estg->set_bg(new road_bg());
		hp=750;
	}
	if(t%960==  1) move_to(0.0,0.35);
	if(t%960==241) move_to(0.2,0.3);
	if(t%960==481) move_to(0.0,0.35);
	if(t%960==721) move_to(-0.2,0.3);
	if(t>180&&t%30==1)
	{
		estg->play_se("se_tan00",0.15);
		for(i=0;i<36;i++)
			for(k=0;k<4;k++)
				estg->add(new straight_bullet(real_x,real_y,hge->Random_Float(0,4),k*0.03+0.15+hge->Random_Float(-0.015,0.015),res->BARROW[k*4]));
	}
}

void marisa_2::nm_3(int t)
{
	if(t==1)
	{
		estg->set_bg(new road_bg());
		hp=750;
	}
	if(t%720==  1) move_to(0.1,0.35);
	if(t%720==181) move_to(0.2,0.3);
	if(t%720==361) move_to(-0.1,0.35);
	if(t%720==541) move_to(-0.2,0.3);
	if(t>180&&t%40==1)
	{
		estg->play_se("se_tan00",0.15);
		estg->add(new sector<>(real_x,real_y,t*0.00074,0.12,res->BARROW[0],false,32,1,0.125,0,0,0));
		estg->add(new sector<>(real_x,real_y,t*0.00074,0.16,res->BARROW[4],false,32,1,0.125,0,0,0));
		estg->add(new sector<>(real_x,real_y,t*0.00074,0.20,res->BARROW[8],false,32,1,0.125,0,0,0));
		estg->add(new sector<>(real_x,real_y,t*0.00074,0.24,res->BARROW[12],false,32,1,0.125,0,0,0));
	}
}

void marisa_2::nm_4(int t)
{
	if(t==1)
	{
		estg->set_bg(new road_bg());
		hp=750;
	}
	if(t%960==  1) move_to(0.0,0.35);
	if(t%960==241) move_to(0.1,0.3);
	if(t%960==481) move_to(0.0,0.35);
	if(t%960==721) move_to(-0.1,0.3);
	if(t>180&&t%6==1)
	{
		estg->play_se("se_tan00",0.1);
		estg->add(new sector<>(real_x,real_y,t*0.01+0.00,0.12,res->BARROW[0],false,5,1,0.8,0,0,0));
		estg->add(new sector<>(real_x,real_y,-t*0.01+0.01,0.16,res->BARROW[4],false,5,1,0.8,0,0,0));
		estg->add(new sector<>(real_x,real_y,t*0.01+0.02,0.20,res->BARROW[8],false,5,1,0.8,0,0,0));
		estg->add(new sector<>(real_x,real_y,-t*0.01+0.03,0.24,res->BARROW[12],false,5,1,0.8,0,0,0));
	}
}

void marisa_2::nm_5(int t)
{
	if(t==1)
	{
		estg->set_bg(new road_bg());
		hp=750;
	}
	if(t%960==  1) move_to(0.0,0.35);
	if(t%960==241) move_to(0.2,0.3);
	if(t%960==481) move_to(0.0,0.35);
	if(t%960==721) move_to(-0.2,0.3);
	if(t>180&&t%60==1)
	{
		estg->play_se("se_tan00",0.15);
		estg->add(new sector<>(real_x,real_y,t*4.16e-4+0.01,0.15,res->BARROW[0],false,64,1,0.0625,0,0,0));
		estg->add(new sector<>(real_x,real_y,t*4.16e-4+0.03,0.16,res->BARROW[4],false,64,1,0.0625,0,0,0));
		estg->add(new sector<>(real_x,real_y,t*4.16e-4+0.05,0.17,res->BARROW[8],false,64,1,0.0625,0,0,0));
		estg->add(new sector<>(real_x,real_y,t*4.16e-4+0.07,0.18,res->BARROW[12],false,64,1,0.0625,0,0,0));
	}
}

void marisa_2::nm_6(int t)
{
	int i;
	if(t==1)
	{
		estg->set_bg(new road_bg());
		hp=750;
	}
	if(t%960==  1) move_to(0.0,0.35);
	if(t%960==241) move_to(0.2,0.3);
	if(t%960==481) move_to(0.0,0.35);
	if(t%960==721) move_to(-0.2,0.3);
	if(t>180&&t%41==1)
	{
		estg->play_se("se_tan00",0.15);
		for(i=0;i<2;i++)
		{
			estg->add(new sector<>(real_x,real_y,hge->Random_Float(-0.1,0.1),0.3+hge->Random_Float(-0.05,0.05),res->BARROW[0],true,5,1,0.8,0,0,0));
			estg->add(new sector<>(real_x,real_y,hge->Random_Float(-0.1,0.1),0.4+hge->Random_Float(-0.05,0.05),res->BARROW[4],true,5,1,0.8,0,0,0));
			estg->add(new sector<>(real_x,real_y,hge->Random_Float(-0.1,0.1),0.5+hge->Random_Float(-0.05,0.05),res->BARROW[8],true,5,1,0.8,0,0,0));
			estg->add(new sector<>(real_x,real_y,hge->Random_Float(-0.1,0.1),0.6+hge->Random_Float(-0.05,0.05),res->BARROW[12],true,5,1,0.8,0,0,0));
			estg->add(new sector<>(real_x,real_y,hge->Random_Float(-0.1,0.1),0.3+hge->Random_Float(-0.05,0.05),res->BARROW[0],true,5,1,0.8,0,0,0));
			estg->add(new sector<>(real_x,real_y,hge->Random_Float(-0.1,0.1),0.4+hge->Random_Float(-0.05,0.05),res->BARROW[4],true,5,1,0.8,0,0,0));
			estg->add(new sector<>(real_x,real_y,hge->Random_Float(-0.1,0.1),0.5+hge->Random_Float(-0.05,0.05),res->BARROW[8],true,5,1,0.8,0,0,0));
			estg->add(new sector<>(real_x,real_y,hge->Random_Float(-0.1,0.1),0.6+hge->Random_Float(-0.05,0.05),res->BARROW[12],true,5,1,0.8,0,0,0));
			estg->add(new sector<>(real_x,real_y,hge->Random_Float(-2,2),0.3+hge->Random_Float(-0.05,0.05),res->BARROW[0],true,5,1,0.8,0,0,0));
			estg->add(new sector<>(real_x,real_y,hge->Random_Float(-2,2),0.4+hge->Random_Float(-0.05,0.05),res->BARROW[4],true,5,1,0.8,0,0,0));
			estg->add(new sector<>(real_x,real_y,hge->Random_Float(-2,2),0.5+hge->Random_Float(-0.05,0.05),res->BARROW[8],true,5,1,0.8,0,0,0));
			estg->add(new sector<>(real_x,real_y,hge->Random_Float(-2,2),0.6+hge->Random_Float(-0.05,0.05),res->BARROW[12],true,5,1,0.8,0,0,0));
		}
		
	}
}

void marisa_2::nm_7(int t)
{
	if(t==1)
	{
		estg->set_bg(new road_bg());
		hp=750;
	}
	if(t%960==  1) move_to(0.0,0.35);
	if(t%960==241) move_to(0.2,0.3);
	if(t%960==481) move_to(0.0,0.35);
	if(t%960==721) move_to(-0.2,0.3);
	if(t>180)
	{
		estg->play_se("se_tan00",0.1);
		estg->add(new sector<>(real_x,real_y,t*0.06,0.15*hge->Random_Float(0.9,1.1),res->BARROW[0],false,2,1,2.0+hge->Random_Float(-0.1,0.1),0,0,0));
		estg->add(new sector<>(real_x,real_y,-t*0.06,0.3*hge->Random_Float(0.9,1.1),res->BARROW[12],false,2,1,2.0+hge->Random_Float(-0.1,0.1),0,0,0));
		if(hge->Random_Int(0,2)==0)
			estg->add(new sector<>(real_x,real_y,-t*0.06,0.4*hge->Random_Float(0.9,1.1),res->BARROW[12],false,2,1,2.0+hge->Random_Float(-0.1,0.1),0,0,0));
	}
}

void marisa_2::nm_8(int t)
{
	int i;
	if(t==1)
	{
		estg->set_bg(new road_bg());
		hp=750;
	}
	if(t%480==  1) move_to(0.1,0.35);
	if(t%480==121) move_to(0.3,0.3);
	if(t%480==241) move_to(-0.1,0.35);
	if(t%480==481) move_to(-0.3,0.3);
	if(t>180)
	{
		t=t%120;
		if(t<40)
		{
			estg->play_se("se_tan00",0.1);
			for(i=0;i<6;i++)
				estg->add(new straight_bullet(real_x+0.15*cos(t/40.0*M_PI),real_y-0.15*sin(t/40.0*M_PI),hge->Random_Float(0,4),hge->Random_Float(0.15,0.2),res->BARROW[0]));
		}
		if(t>60&&t<100)
		{
			estg->play_se("se_tan00",0.1);
			t=t-60;
			for(i=0;i<5;i++)
				estg->add(new straight_bullet(real_x-0.15*cos(t/40.0*M_PI),real_y-0.15*sin(t/40.0*M_PI),hge->Random_Float(0,4),hge->Random_Float(0.3,0.4),res->BARROW[12]));
		}
	}
}

void marisa_2::nm_9(int t)
{
	if(t==1)
	{
		estg->set_bg(new road_bg());
		hp=750;
	}
	if(t%960==  1) move_to(0.1,0.35);
	if(t%960==241) move_to(0.3,0.3);
	if(t%960==481) move_to(-0.1,0.35);
	if(t%960==721) move_to(-0.3,0.3);
	if(t>180&&t%120==30)
	{
		estg->play_se("se_tan00",0.15);
		estg->add(new sector<acc_str_bullet>(real_x,real_y,+t*1.2345,0.1,res->BARROW[0],false,80,1,0.05,0,0,0,0,0,0,+0.03,0,0));
		estg->add(new sector<acc_str_bullet>(real_x,real_y,-t*1.2345,0.1,res->BARROW[0],false,80,1,0.05,0,0,0,0,0,0,-0.03,0,0));
		estg->add(new sector<acc_str_bullet>(real_x,real_y,+t*1.2345,0.2,res->BARROW[12],false,64,1,0.0625,0,0,0,0,0,0,+0.03,0,0));
		estg->add(new sector<acc_str_bullet>(real_x,real_y,-t*1.2345,0.2,res->BARROW[12],false,64,1,0.0625,0,0,0,0,0,0,-0.03,0,0));
	}
}

void marisa_2::escape(int t)
{
	suffer=false;
	if(t==60)
	{
		estg->set_bg(new road_bg());
		move_to(0.54,0.64,120);
	}
	if(t==180) destroy();
}

marisa_2::~marisa_2()
{
	
}

void marisa_2::kill()
{
	estg->play_se("se_enep01",0.25);
	age=(age/SC_OS)*SC_OS+SC_OS;
	hp=MAX_HP;
	estg->destroy_all_enemy();
}

marisa_2_1_laser::marisa_2_1_laser(int index):laser((index%2)*6)
{
	cx=0;
	cy=0.3;
	r0=0.015;
	x0=0.2+(index%4)*0.1;
	crot=index*0.0625;
	has_aura=true;
	node=-1;
	if(index%2==0)
		aura_spin*=-1;
}

void marisa_2_1_laser::loop()
{
	laser::loop();
	if(age>360)
	{
		if(age%360==1)
			turn_on(60);
		if(age%360>31&&age%360<121)
			turn_on_sts++;
		if(age%360==241)
			turn_off();
		if(age%360==271)
			rot=hge->Random_Float(-0.5,0.5);
		if(age%360>151&&age%360<241)
			crot+=0.00023*(this->_type-3);
		if(age%360==121)
			estg->play_se("se_lazer00",0.1);
	}
	else if(age<60)
	{
		node=0.75*age/60.0;
		x=x0*age/60.0;
		crot+=0.0021*(this->_type-3);
	}
	else
	{
		crot+=0.0021*(this->_type-3);
	}
}

marisa_2_2_minion::marisa_2_2_minion(bullet* _master,int index):minion(_master)
{
	suffer=false;
	img=res->img["minion"];
	layer=ENEMY_LAYER+1;
	crot=index*0.8;
	x=0;
}

void marisa_2_2_minion::loop()
{
	minion::loop();
	if(!dead)
	{
		if(age<=30) x=age*0.005;
		cx=master->real_x;
		cy=master->real_y;
		crot+=0.03;
		if(age%11==5)
		{
			estg->play_se("se_tan00",0.05);
			estg->add(new straight_bullet(real_x,real_y,crot-0.18,0.3,res->SSTAR[4],false,0,-2,0,ENEMY_BULLET_LAYER));
			estg->add(new straight_bullet(real_x,real_y,crot+0.02,0.2,res->SSTAR[6],false,0,2,0,ENEMY_BULLET_LAYER));
			estg->add(new straight_bullet(real_x,real_y,crot+0.23,0.15,res->SSTAR[2],false,0,-2,0,ENEMY_BULLET_LAYER));
		}
		if(age%26==5)
			estg->add(new straight_bullet(real_x,real_y,0,0.375,res->SSTAR[13],true,0,2,0,ENEMY_BULLET_LAYER));
	}
}

marisa_2_2_laser::marisa_2_2_laser(float x0, float y0)
{
	x=x0;y=y0;
	r0=0.08;
	rot=-1.0;
	l1=0.4;
	node0=2.0;
	_type=4;
}

void marisa_2_2_laser::loop()
{
	laser::loop();
	node=node0*r/r0;
	if(age==1)
	{
		turn_on(15);
		estg->play_se("se_lazer00",0.3);
	}
	if(age==91) turn_off();
	if(age==121) destroy();
}

marisa_2_3_laser::marisa_2_3_laser(float x0,float y0,float rot0,int type):laser(type)
{
	cx=x0;cy=y0;
	crot=rot0;
	c=0xFF808080;
	r0=0.015;
	l2=1.2;
}

void marisa_2_3_laser::loop()
{
	laser::loop();
	if(age==1) turn_on();
	if(age>=15&&age<45) turn_on_sts++;
	if(age==60)
	{
		c=0xFFFFFFFF;
		estg->play_se("se_lazer00",0.3);
	}
	if(age==270) turn_off();
	if(age==300) destroy();
}

marisa_2_3_minion::marisa_2_3_minion(bullet* _master,int index):minion(_master)
{
	suffer=false;
	img=res->img["minion"];
	layer=ENEMY_LAYER+1;
	crot=index*0.8;
	x=0.05;
}

void marisa_2_3_minion::loop()
{
	minion::loop();
	if(!dead)
	{
		cx=master->real_x;
		cy=master->real_y;
		crot+=0.048;
		if(age%53==5)
		{
			estg->play_se("se_tan00",0.05);
			estg->add(new sector<>(real_x,real_y,crot+0.3,0.11,res->SSTAR[2],false,10,1,0.015,0,0,0,0,0,0,-2,0,0));
			estg->add(new sector<>(real_x,real_y,crot+0.0,0.11,res->SSTAR[4],false,10,1,0.015,0,0,0,0,0,0,+2,0,0));
			estg->add(new sector<>(real_x,real_y,crot-0.3,0.11,res->SSTAR[6],false,10,1,0.015,0,0,0,0,0,0,-2,0,0));
		}
	}
}

marisa_2_4_laser::marisa_2_4_laser(int index)
{
	_index=index;
	_type=2*(index%3);
	if(index<6) crot=2.333333;
	node=1.5;
	l1=0.15;
	l2=0.2;
	r0=0.02;
	has_aura=true;
}

void marisa_2_4_laser::loop()
{
	laser::loop();
	if(age<720)
	{
		if(_index<6) crot+=0.0222222;
		else crot-=0.0222222;
		if(x<0.4) x+=0.00125;
	}
	else
	{
		if(age%720==120)
		{
			estg->play_se("se_lazer00",0.1);
			turn_on();
		}
		if(age%720>210&&age%720<300)
			rot=(age%720-210)*(2*(_index%2)-1)*0.0185185;
		if(age%720==360) turn_off();
		if(age%720==390) rot=0;
		if(age%720>=390&&age%720<690) crot+=(2*(_index%2)-1)*0.00555555;
	}
}

marisa_2_4_star::marisa_2_4_star(float rot0,float speed)
{
	crot=rot0;
	_speed=speed;
	img=res->SSTAR[hge->Random_Int(1,5)*2];
}

void marisa_2_4_star::loop()
{
	if(age<90)
	{
		x+=_speed;
		rot+=0.03;
	}
	if(age==90)
	{
		update_xy();
		cx=real_x;
		cy=real_y;
		x=0;
		crot=2+crot+hge->Random_Float(-1.8,+1.8);
	}
	if(age>240)
	{
		x+=0.002;
		rot-=0.03;
	}
}

marisa_2_5_comet::marisa_2_5_comet()
{
	suffer=false;
	img=res->img["comet"];
	y=0.3;
}

void marisa_2_5_comet::loop()
{
	float a=v2a(estg->self->real_x-real_x,estg->self->real_y-real_y);
	x+=0.002*cos(a*M_PI_2);
	y+=0.002*sin(a*M_PI_2);
	if(age%5==3)
	{
		estg->play_se("se_kira00",0.1);
		estg->add(new marisa_1_2_bullet(real_x,real_y,hge->Random_Float(0,4),0.2,0,8,res->SSTAR[2],(2*(age%2)-1)*0.03));
	}
}

marisa_2_6_bullet::marisa_2_6_bullet(int index,float x0,float y0)
{
	x=x0;
	y=y0;
	_index=index;
	img=res->EYE[0];
	_type=hge->Random_Int(0,7);
	attack=false;
	suffer=false;
	estg->play_se("se_option",0.2);
	layer=SELF_LAYER-1;
}

void marisa_2_6_bullet::loop()
{
	if(age==25) attack=true;
	if(_index<(estg->sres.val["sc6"]-32))
	{
		estg->play_se("se_tan00",0.15);
		int i;
		for(i=0;i<8;i++)
			estg->add(new straight_bullet(real_x,real_y,hge->Random_Float(0,4),hge->Random_Float(0.1,0.3),res->BARROW[_type*2]));
		dead=true;
	}
}

void marisa_2_6_bullet::draw()
{
	res->img["enemy_aura"]->RenderEx(x2scr(real_x),y2scr(real_y),-estg->ticker*0.01,0.5);
	if(age>25)
		res->PREMASK[_type]->RenderEx(x2scr(real_x),y2scr(real_y),estg->ticker*0.01);
	else
		res->PREMASK[_type]->RenderEx(x2scr(real_x),y2scr(real_y),estg->ticker*0.01,0.08*age);
}

marisa_2_7_laser::marisa_2_7_laser(int index)
{
	x=0.125;
	crot0=v2a(estg->self->real_x,estg->self->real_y);
	crot=index*0.8+crot0;
	if(index==4) _type=7;
	else _type=index*2;
	turn_on(60);
	node=1;
	has_aura=true;
	r0=0.03;
}

void marisa_2_7_laser::loop()
{
	laser::loop();
	if(age==60)
	{
		estg->play_se("se_lazer00",0.3);
		float drot=fmod(v2a(estg->self->real_x,estg->self->real_y)-crot0,4.0f);
		if(drot<0) drot+=4.0;
		if(drot<2) rot_dir=0.003;
		else rot_dir=-0.003;
	}
	if(age>60&&age<660) crot+=rot_dir;
	if(age==660) turn_off();
	if(age==690) destroy();
}

marisa_2_7_bullet::marisa_2_7_bullet(float x0,float y0,float angle,float speed,pic *image,bool aim,float acc,float vrot,int _layer)
:acc_str_bullet(x0,y0,angle,speed,image,aim,acc,vrot,_layer)
{
	spin=hge->Random_Int(0,1)*2-1;
	img=res->SSTAR[hge->Random_Int(1,5)*2];
}

void marisa_2_7_bullet::loop()
{
	x=age*_speed+0.5*age*age*_acc;
	if(age>40) crot+=_vrot;
	rot+=spin*0.03;
}

marisa_2_8_bullet::marisa_2_8_bullet(float x0,float y0,float angle,float speed,pic* image,int index,int index2)
:straight_bullet(x0,y0,angle,speed,image)
{
	_index=index;
	_index2=index2;
}

void marisa_2_8_bullet::loop()
{
	straight_bullet::loop();
	if(age==90)
	{
		if(_index%2==0)
		{
			if(_index<90)
				estg->add(new straight_bullet(real_x,real_y,crot+(_index%5)*0.3-0.6,0.1+_index*0.005,res->BARROW[8]));
			else
				estg->add(new straight_bullet(real_x,real_y,crot-(_index%5)*0.3+0.6,0.1+(_index-90)*0.005,res->BARROW[4]));
		}
		if(_index== 1&&_index2%5==0)
			estg->add(new marisa_2_8_bullet2(real_x,real_y,crot-2.4,0.115,res->BARROW[0]));
		if(_index==91&&_index2%5==0)
			estg->add(new marisa_2_8_bullet2(real_x,real_y,crot-1.6,0.115,res->BARROW[0]));
		destroy();
	}
}

marisa_2_8_bullet2::marisa_2_8_bullet2(float x0,float y0,float angle,float speed,pic *image)
:straight_bullet(x0,y0,angle,speed,image)
{
}

void marisa_2_8_bullet2::loop()
{
	straight_bullet::loop();
	if(age==240)
	{
		estg->play_se("se_kira00",0.07);
		estg->add(new sector<>(real_x,real_y,crot,0.22,res->BARROW[0],false,11,1,0.14,0,0,0));
		estg->add(new sector<>(real_x,real_y,crot,0.25,res->BARROW[0],false,10,1,0.14,0,0,0));
		destroy();
	}
}

marisa_2_9_minion::marisa_2_9_minion(float x0,float y0)
{
	has_aura=true;
	x=x0;
	y=y0;
}

void marisa_2_9_minion::loop()
{
	laser::loop();
	if(age<60) node=0.025*age;
	if(age%30==0&&age>60)
	{
		estg->add(new marisa_2_9_laser(real_x,real_y));
		if(age%60==0)
			estg->play_se("se_lazer00",0.2);
	}
}

marisa_2_9_laser::marisa_2_9_laser(float x0,float y0)
{
	r0=0.017;
	l2=0.0;
	l1=0.15;
	cx=x0;
	cy=y0;
	crot=v2a(estg->self->real_x-x0,estg->self->real_y-y0);
	x=-0.05;
	node=-1.0;
	_type=hge->Random_Int(0,7);
	turn_on();
}

void marisa_2_9_laser::loop()
{
	laser::loop();
	x+=0.005;
}

marisa_2_10_bullet::marisa_2_10_bullet(float x0,float y0,float angle,float speed,pic *image)
{
	cx=x0;
	cy=y0;
	_vx=speed*cos(angle*M_PI_2)/60.0;
	_vy=speed*sin(angle*M_PI_2)/60.0;
	vxf=_vx*0.2;
	vyf=-(_vy*0.2+0.2)/60.0;
	if(image!=res->img["comet_fast"])
		vyf=_vy;
	else
		auto_clear=false;
	img=image;
	spin=(hge->Random_Int(0,1)*2-1)*0.03;
}

void marisa_2_10_bullet::loop()
{
	x=vxf*age+(_vx-vxf)*75.0*(1-exp(-age/75.0));
	y=vyf*age+(_vy-vyf)*75.0*(1-exp(-age/75.0));
	rot+=spin;
	if(real_y<-0.6||fabs(real_x)>0.5) destroy();
}
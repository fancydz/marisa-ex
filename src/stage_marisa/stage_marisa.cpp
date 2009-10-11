#include "stage_marisa.h"
#include <ESTG.h>
#include "stage_marisa_enemy.h"
#include "marisa_bg.h"
#include "boss\\marisa_1.h"
#include "boss\\marisa_2.h"

stage_marisa::stage_marisa()
{
	//load resources for this stage.
	estg->sres.TEX["marisa_bg1"]=hge->Texture_Load("img\\7-1.png");
	estg->sres.img["marisa_bg1"]=new pic(estg->sres.TEX["marisa_bg1"],0,0,256,256);
	estg->sres.TEX["marisa_bg2"]=hge->Texture_Load("img\\7-2.png");
	estg->sres.img["marisa_bg2"]=new pic(estg->sres.TEX["marisa_bg2"],0,0,256,256);
	estg->sres.TEX["forest"]=hge->Texture_Load("img\\forest.png");
	estg->sres.img["trunk"]=new pic(estg->sres.TEX["forest"],490,0,21,512);
	estg->sres.img["trunk"]->SetHotSpot(9,0);
	estg->sres.img["leaf_1"]=new pic(estg->sres.TEX["forest"],1,257,293,254);
	estg->sres.img["leaf_2"]=new pic(estg->sres.TEX["forest"],257,1,234,197);
	estg->sres.img["ground0"]=new pic(estg->sres.TEX["forest"],1,1,127,127);
	estg->sres.img["ground1"]=new pic(estg->sres.TEX["forest"],1,128,127,127);
	estg->sres.img["ground2"]=new pic(estg->sres.TEX["forest"],128,1,127,127);
	estg->sres.img["ground3"]=new pic(estg->sres.TEX["forest"],128,128,127,127);
	estg->sres.TEX["marisa_boss"]=hge->Texture_Load("img\\marisa.png");
	estg->sres.snd["th06_14"]=new estg_se("bgm\\th06_14.mp3");
	estg->play_bgm(estg->sres.snd["th06_14"]->se,155.0,117.45639455782312925170068027211);
	
	//create background
	estg->set_bg(new road_bg());
	
	//register itself to stage_master
	estg->stage_master=this;
	//
	//
	//age=10600;
	age=5900;
	//
}

stage_marisa::~stage_marisa()
{
	estg->sres.clear();
}

void stage_marisa::loop()
{
	int i;
	//
	if(age==240)
		for(i=0;i<10;i++)
			estg->add(new stage_marisa_wave_2(i*20,120-i*12,+1));
			
	if(age==840)
		for(i=0;i<4;i++)
			(*estg->add(new stage_marisa_wave_8((i-1.5)*0.25,0.3+(i%2)*0.05)))->age=-i*10;
			
	if(age==1440)
		for(i=0;i<10;i++)
			estg->add(new stage_marisa_wave_2(i*20,120-i*12,-1));
	if(age==2100)
		for(i=0;i<6;i++)
			(*estg->add(new stage_marisa_wave_10((i-2.5)*0.15,0.35+(i%2)*0.15)))->age=-i*10;
	if(age==2760)
		estg->add(new stage_marisa_wave_3(0.3,0.35));
		
	if(age==2766)
		estg->add(new stage_marisa_wave_3(-0.3,0.35));
		
	if(age==3420)
		for(i=0;i<4;i++)
		{
			(*estg->add(new stage_marisa_wave_11((i-1.6)*0.25,0.45)))->age=-i*20;
			(*estg->add(new stage_marisa_wave_14((1.6-i)*0.25,0.35)))->age=-i*20;
		}
		
	if(age==4200)
		for(i=0;i<5;i++)
			{
				estg->add(new stage_marisa_wave_6(+1,i));
				estg->add(new stage_marisa_wave_6(-1,i));
			}
	if(age==4260)
		estg->add(new stage_marisa_wave_5(0));
	
	if(age==5040)
	{
		for(i=0;i<4;i++)
			(*estg->add(new stage_marisa_wave_9((1.5-i)*0.25,0.35)))->age=-i*20;
		for(i=0;i<6;i++)
		{
			(*estg->add(new stage_marisa_wave_13(+1,i*6)))->age=-i*20;
			(*estg->add(new stage_marisa_wave_13(-1,i*6)))->age=-i*20-200;
		}
	}
	if(age==5910)
		estg->add(new marisa_1(-0.54,0.64));
		
	if(age>6000&&age<9160&&age%840==150)
	{
		for(i=0;i<8;i++)
			switch(hge->Random_Int(0,5))
			{
				case 0:
				{
					(*estg->add(new stage_marisa_wave_8((i-3.5)*0.12,0.35+(i%2)*0.05)))->age=-i*20;
					break;
				}
				case 1:
				{
					(*estg->add(new stage_marisa_wave_9((i-3.5)*0.12,0.35+(i%2)*0.05)))->age=-i*20;
					break;
				}
				case 2:
				{
					(*estg->add(new stage_marisa_wave_10((i-3.5)*0.12,0.35+(i%2)*0.05)))->age=-i*20;
					break;
				}
				case 3:
				{
					(*estg->add(new stage_marisa_wave_11((i-3.5)*0.12,0.35+(i%2)*0.05)))->age=-i*20;
					break;
				}
				case 4:
				{
					(*estg->add(new stage_marisa_wave_14((i-3.5)*0.12,0.35+(i%2)*0.05)))->age=-i*20;
					break;
				}
				default:
				{
					(*estg->add(new stage_marisa_wave_4((i-3.5)*0.12,0.35+(i%2)*0.05)))->age=-i*20;
					break;
				}
			}
	}
	
	if(age==9560)
		estg->add(new stage_marisa_wave_15(0));
	
	if(age==10640)
		estg->add(new marisa_2(-0.54,0.64));
	
	if(age==10670)
		age=0;
	}

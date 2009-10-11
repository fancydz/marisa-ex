#include "common_res.h"
#include <hge.h>
#include <hgefont.h>

using namespace std;

bool charcmp::operator()(const char* lhs,const char* rhs)const
{
	return strcmp(lhs,rhs)<0;
}

estg_se::estg_se(char* snd_file)
{
	ch=0;
	vol=0.0;
	se=hge->Effect_Load(snd_file);
}

estg_se::~estg_se()
{
	hge->Effect_Free(se);
}

void resource::clear()
{
	map<char*,HTEXTURE,charcmp>::iterator tex_it;
	map<char*,pic*,charcmp>::iterator img_it;
	map<char*,estg_se*,charcmp>::iterator snd_it;
	map<char*,float,charcmp>::iterator val_it;
	for(tex_it=TEX.begin();tex_it!=TEX.end();tex_it++)
		hge->Texture_Free(tex_it->second);
	for(snd_it=snd.begin();snd_it!=snd.end();snd_it++)
		delete snd_it->second;
	for(img_it=img.begin();img_it!=img.end();img_it++)
		delete img_it->second;
	TEX.clear();
	img.clear();
	snd.clear();
	val.clear();
	blt.clear();
}

resource::~resource()
{
	clear();
}

cres::cres()
{
	//load textures
	TEX["common_1"]=hge->Texture_Load("img\\common_1.png");
	TEX["common_2"]=hge->Texture_Load("img\\common_2.png");
	TEX["common_3"]=hge->Texture_Load("img\\common_3.png");
	TEX["common_4"]=hge->Texture_Load("img\\common_4.png");
	TEX["particles"]=hge->Texture_Load("img\\particles.png");
	TEX["girl_tex"]=hge->Texture_Load("img\\enemy.png");
	TEX["ui_bg"]=hge->Texture_Load("img\\UI_bg.png");
	int i,j;
	//load images from common_1
	for(i=0;i<8;i++)
		BSTAR[i]=new pic(TEX["common_1"],i*32,0,32,32,6,6);
	for(i=0;i<16;i++)
		SSTAR[i]=new pic(TEX["common_1"],i*16+0.2,32.2,15.6,15.6,3,3);
	for(i=0;i<16;i++)
		SRICE[i]=new pic(TEX["common_1"],i*16,48,16,16,3,3);
	for(i=0;i<4;i++)
		EYE[i]=new pic(TEX["common_1"],i*64,64,64,64,20,20);
	for(i=0;i<16;i++)
		WHEAT[i]=new pic(TEX["common_1"],i*16,128,16,16,3,3);
	for(i=0;i<16;i++)
		SPARK[i]=new pic(TEX["common_1"],i*16,144,16,16,"img\\spark.psi");
	for(i=0;i<16;i++)
		SPARK2[i]=new pic(TEX["common_1"],i*16,144,16,16,"img\\spark2.psi");
	for(i=0;i<16;i++)
		SARROW[i]=new pic(TEX["common_1"],i*16,160,16,16,3,3);
	for(i=0;i<8;i++)
		BALL3[i]=new pic(TEX["common_1"],i*32+1,176+1,30,30,10,10);
	for(i=0;i<8;i++)
		KNIFE[i]=new pic(TEX["common_1"],i*32,208,32,32,4,12);
	for(i=0;i<16;i++)
		BALL0[i]=new pic(TEX["common_1"],i*16,240,16,16,2,2);
	//load images from common_2
	for(i=0;i<8;i++)
		BRICE[i]=new pic(TEX["common_2"],i*32,0,32,32,5,8);
	for(i=0;i<16;i++)
		BULLET[i]=new pic(TEX["common_2"],i*16,32,16,16,3,3);
	for(i=0;i<16;i++)
		VOIDBULLET[i]=new pic(TEX["common_2"],i*16,192,16,16);
	for(i=0;i<8;i++)
	{
		BALL2[i]=new pic(TEX["common_2"],i*32+8,56,16,16,5,5);
		BALL2[i+8]=new pic(TEX["common_2"],i*32+8,216,16,16,5,5);
	}
	for(i=0;i<16;i++)
		SQUARE[i]=new pic(TEX["common_2"],i*16,80,16,16,3,4,true);
	for(i=0;i<8;i++)
		BUTTERFLY[i]=new pic(TEX["common_2"],i*32,96,32,32,4,4);
	for(i=0;i<16;i++)
		LARVE[i]=new pic(TEX["common_2"],i*16,128,16,16,3,3);
	for(i=0;i<8;i++)
	{
		PREMASK[i]=new pic(TEX["common_2"],i*32+0.5,144.5,31,31);
		PREMASK[i]->SetBlendMode(BLEND_COLORMUL|BLEND_ALPHAADD|BLEND_NOZWRITE);
	}
	for(i=0;i<16;i++)
		POSTMASK[i]=new pic(TEX["common_2"],i*16,176,16,16);
	for(i=0;i<16;i++)
		BARROW[i]=new pic(TEX["common_2"],i*16,240,16,16,4,4);
	//load images from common_3
	img["self_aura1"]=new pic(TEX["common_3"],128,112,64,64);
	img["self_aura2"]=new pic(TEX["common_3"],0,112,64,64);
	img["circle"]=new pic(TEX["common_3"],64,208,32,32);
	img["blue_bubble"]=new pic(TEX["common_3"],192,176,64,64);
	img["orange_bubble"]=new pic(TEX["common_3"],0,176,64,64);
	img["enemy_aura"]=new pic(TEX["common_3"],192,112,64,64);
	img["yin"]=new pic(TEX["common_3"],96,64,16,16,4,4);
	//load images from common_4
	for(i=0;i<16;i++)
		BALL1[i]=new pic(TEX["common_4"],i*16+.5,.5,15,15,4,4);
	for(i=0;i<16;i++)
		YONG[i]=new pic(TEX["common_4"],i*16+1,17,14,14,4,4);
	for(i=0;i<16;i++)
		POINT[i]=new pic(TEX["common_4"],i*16+1,33,14,14,4,4);
	img["black"]=new pic(TEX["common_4"],80,208,32,32);
	img["err"]=new pic(TEX["common_4"],1,193,62,62,32,32);
	img["spectrum"]=new pic(TEX["common_4"],4,50,128,2);
	//test
	TEX["test"]=hge->Texture_Load("img\\pearlbullet.png");
	img["test"]=new pic(TEX["test"],0,0,32,32,4,4,true);
	TEX["test_rice"]=hge->Texture_Load("img\\rice.png");
	for(i=0;i<16;i++)
		SRICE[i]=new pic(TEX["test_rice"],i*16,0,16,16,3,3);
	TEX["test_arrow"]=hge->Texture_Load("img\\arrow.png");
	for(i=0;i<16;i++)
		BARROW[i]=new pic(TEX["test_arrow"],i*16,104,16,16,3,3);
	//laser
	TEX["laser"]=hge->Texture_Load("img\\laser.png");
	LASER=new hgeDistortionMesh(5,2);
	LASER->SetTexture(TEX["laser"]);
	LASER->SetBlendMode(BLEND_COLORMUL|BLEND_ALPHAADD|BLEND_NOZWRITE);
	//load particle systems
	img["minion"]=new pic(TEX["particles"],64,64,32,32,"img\\minion.psi",10,10);
	img["cannon"]=new pic(TEX["particles"],32,32,32,32,"img\\cannon.psi",8,8);
	img["comet"]=new pic(TEX["particles"],0,0,32,32,"img\\comet.psi",6,6);
	img["comet_fast"]=new pic(TEX["particles"],0,0,32,32,"img\\comet_fast.psi",8,8);
	img["cannon-warn"]=new pic(TEX["particles"],32,32,32,32,"img\\cannon-warn.psi",16,16);
	//image for girls
	for(i=0;i<16;i++)
		for(j=0;j<8;j++)
			GIRL_IMG[i][j]=new pic(TEX["girl_tex"],j*32,i*32,32,32,24,24);
	//UIs
	img["ui_bg_1"]=new pic(TEX["ui_bg"],0,0,8,480);
	img["ui_bg_2"]=new pic(TEX["ui_bg"],392,0,248,480);
	img["ui_bg_3"]=new pic(TEX["ui_bg"],8,0,384,8);
	img["ui_bg_4"]=new pic(TEX["ui_bg"],8,472,384,8);
	//load wavs
	snd["se_plst00"]=new estg_se("snd\\se_plst00.wav");
	snd["se_damage00"]=new estg_se("snd\\se_damage00.wav");
	snd["se_enep00"]=new estg_se("snd\\se_enep00.wav");
	snd["se_enep01"]=new estg_se("snd\\se_enep01.wav");
	snd["se_pldead00"]=new estg_se("snd\\se_pldead00.wav");
	snd["se_tan00"]=new estg_se("snd\\se_tan00.wav");
	snd["se_tan01"]=new estg_se("snd\\se_tan01.wav");
	snd["se_tan02"]=new estg_se("snd\\se_tan02.wav");
	snd["se_lazer00"]=new estg_se("snd\\se_lazer00.wav");
	snd["se_kira00"]=new estg_se("snd\\se_kira00.wav");
	snd["se_kira01"]=new estg_se("snd\\se_kira01.wav");
	snd["se_item00"]=new estg_se("snd\\se_item00.wav");
	snd["se_item01"]=new estg_se("snd\\se_item01.wav");
	snd["se_graze"]=new estg_se("snd\\se_graze.wav");
	snd["se_option"]=new estg_se("snd\\se_option.wav");
	
}

cres::~cres()
{
	
}

#ifndef COMMON_RES_H
#define COMMON_RES_H
#include <hge.h>
#include <hgefont.h>
#include <hgedistort.h>
#include <map>
#include <string>
#include <ESTG_img.h>

using namespace std;

struct charcmp {
	bool operator()(const char* lhs,const char* rhs)const;
};

#define SND_FACTOR 20.0

class estg_se
{
public:
	HEFFECT se;
	HCHANNEL ch;
	float vol;
	estg_se(char* snd_file);
	~estg_se();
};

class resource
{
public:
	map<char*,HTEXTURE,charcmp> TEX;
	map<char*,pic*,charcmp> img;
	map<char*,estg_se*,charcmp> snd;
	map<char*,float,charcmp> val;
	map<char*,void*,charcmp> blt;
	void clear();
	~resource();
};

class cres : public resource
{
public:
	//
	pic* BSTAR[8];
	pic* SSTAR[16];
	pic* SRICE[16];
	pic* EYE[4];
	pic* WHEAT[16];
	pic* SPARK[16];
	pic* SPARK2[16];
	pic* SARROW[16];
	pic* BALL3[8];
	pic* KNIFE[8];
	pic* BALL0[16];
	//
	pic* BRICE[8];
	pic* BULLET[16];
	pic* VOIDBULLET[16];
	pic* BALL2[16];
	pic* SQUARE[16];
	pic* BUTTERFLY[8];
	pic* LARVE[16];
	pic* PREMASK[8];
	pic* POSTMASK[16];
	pic* BARROW[16];
	//
	pic* BALL1[16];
	pic* YONG[16];
	pic* POINT[16];
	//
	hgeDistortionMesh* LASER;
	//
	hgeFont* fnt;
	pic* graze;
	//
	pic* GIRL_IMG[16][8];
	cres();
	~cres();
};
extern HGE* hge;
#endif
